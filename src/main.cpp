// Main run loop for "A Tree's Life".

// TODO: Remove unused imports.
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Mathematics
#define GLM_FORCE_RADIANS  // force everything in radian
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

#include "Light.h"
#include "Plane.h"
#include "PlaneResourceManager.h"
#include "Segment.h"
#include "SegmentResourceManager.h"
#include "Skybox.h"
#include "Tree.h"
#include "World.h"

// UGH is there a way to get rid of this global??
World* g_world;
SegmentResourceManager* g_segment_resource_manager;
World* createWorld(GLFWwindow* window);
World* createGrove(GLFWwindow* window);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];

GLFWwindow* setupWindow() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return NULL;
  }

  // Set required options for GLFW.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  /* Create a windowed mode window and its OpenGL context */
  GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to initialize window" << std::endl;
    glfwTerminate();
    return NULL;
  }
  glfwMakeContextCurrent(window);

  // Don't show the cursor.
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Set this to true so GLEW knows to use a modern approach to retrieving
  // function pointers and extensions
  glewExperimental = GL_TRUE;

  // Initialize GLEW to setup the OpenGL Function pointers
  glewInit();

  // Define the viewport dimensions
  int w, h;
  glfwGetFramebufferSize(window, &w, &h);
  glViewport(0, 0, w, h);

  return window;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS) {
      keys[key] = true;
    } else if (action == GLFW_RELEASE) {
      keys[key] = false;
      if (key == GLFW_KEY_2) {
        // TODO: Do something.
      } else if (key == GLFW_KEY_P) {
        g_world->togglePause();
      } else if (key == GLFW_KEY_B) {
        g_world->toggleBreeze();
      }
/*
      } else if (key == GLFW_KEY_G) {
        cout << "G" << endl;
        if (g_world) delete g_world;
        g_world = createGrove(window);
      } else if (key == GLFW_KEY_R) {
        cout << "R" << endl;
        if (g_world) delete g_world;
        cout << "k" << endl;
        g_world = createWorld(window);
        cout << "L" << endl;
      }
*/
    }
  }
}

// Control camera movement with mouse motion
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  GLfloat xoffset = xpos - lastX;
  GLfloat yoffset =
      lastY - ypos;  // Reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  g_world->m_camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  g_world->m_camera->ProcessMouseScroll(yoffset);
}

void setupInputHandlers(GLFWwindow* window) {
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
}

// Create a world with a single tree.
World* createWorld(GLFWwindow* window) {
  World* world = new World(window);

  world->addEntity(new Skybox(world->m_skybox_shader, world->m_camera, window));
  world->addEntity(new Plane(world->m_shader, world->m_camera, window));

  world->addEntity(new Tree(world->m_shader, glm::vec3(0.0f, 0.0f, 0.0f), 5.0,
                            g_segment_resource_manager, world->m_camera, window,
                            false));

  world->addEntity(new Light(world->m_shader, glm::vec3(0.0f, 20.0f, -9.0f)));
  world->addEntity(new Light(world->m_shader, glm::vec3(0.0f, 20.0f, 9.0f)));
  world->addEntity(new Light(world->m_shader, glm::vec3(-9.0f, 9.0f, 9.0f)));
        cout << "k" << endl;

  return world;
}

// Create a world with multiple trees.
World* createGrove(GLFWwindow* window) {
  cout << "Creating grove" << endl;

  World* world = new World(window);

  world->addEntity(new Skybox(world->m_skybox_shader, world->m_camera, window));
  world->addEntity(new Plane(world->m_shader, world->m_camera, window));

  // Create Game of Thrones tree
  glm::vec3 got_location = glm::vec3(0.0f, 0.0f, -10.0f);
  world->addEntity(new Tree(world->m_shader, got_location, 5.0,
                            g_segment_resource_manager, world->m_camera,
                            window, true));

  // Create other trees.
  int num_trees = 10;
  for (int i = 0; i < num_trees; i++) {
    glm::vec2 random_vector = glm::diskRand<float>(18.0);
    glm::vec3 location = glm::vec3(random_vector[0], 0.0f,
        random_vector[1]) + got_location;
    while (glm::distance2(location, got_location) < 5.0) {
      random_vector = glm::diskRand<float>(15.0);
      location = glm::vec3(random_vector[0], 0.0f,
          random_vector[1]) + got_location;
    }

    float size = glm::linearRand<float>(0.5, 5.0);
    world->addEntity(new Tree(world->m_shader, location, size,
                              g_segment_resource_manager, world->m_camera,
                              window, false));
  }

  world->addEntity(new Light(world->m_shader, glm::vec3(9.0f, 9.0f, 9.0f)));
  world->addEntity(new Light(world->m_shader, glm::vec3(0.0f, 9.0f, 9.0f)));
  world->addEntity(new Light(world->m_shader, glm::vec3(-9.0f, 9.0f, 9.0f)));

  return world;

}

// Control camera movement with keyboard keys
void handleInput(World* world, GLfloat deltaTime) {
  glfwPollEvents();

  if (!world || !world->m_camera) {
    return;
  }

  if (keys[GLFW_KEY_W]) world->m_camera->ProcessKeyboard(FORWARD, deltaTime);
  if (keys[GLFW_KEY_S]) world->m_camera->ProcessKeyboard(BACKWARD, deltaTime);
  if (keys[GLFW_KEY_A]) world->m_camera->ProcessKeyboard(LEFT, deltaTime);
  if (keys[GLFW_KEY_D]) world->m_camera->ProcessKeyboard(RIGHT, deltaTime);
}

int main(int argc, char** argv) {
  srand(time(NULL));

  GLFWwindow* window = setupWindow();
  if (!window) {
    return -1;
  }

  setupInputHandlers(window);
  g_segment_resource_manager = new SegmentResourceManager();

  g_world = createWorld(window);
//  g_world = createGrove(window);

  // Set up variables for time calculations.
  GLfloat deltaTime = 0.0f;
  GLfloat timeOfLastFrame = 0.0f;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    GLfloat timeOfCurrentFrame = glfwGetTime();
    deltaTime = timeOfCurrentFrame - timeOfLastFrame;
    timeOfLastFrame = timeOfCurrentFrame;

    handleInput(g_world, deltaTime);
    g_world->update(deltaTime);
    g_world->render();
  }

  glfwTerminate();
  return 0;
}
