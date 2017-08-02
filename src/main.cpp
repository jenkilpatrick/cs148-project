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

#include "Light.h"
#include "World.h"
#include "Segment.h"
#include "SegmentResourceManager.h"

World * createWorld(GLFWwindow * window) {
  // TODO: Use unique pointers.
  // Create the world.
  World * world = new World(window);

  std::cout << "Got here2" << endl;

  // Add objects to the world.
  float radius = 2.0f;
  glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
  float height = 5.0f;
  SegmentResourceManager * segment_resource_manager =
      new SegmentResourceManager();

  std::cout << "Got here3" << endl;
  Segment * segment = new Segment(world->m_shader, radius, position, height,
      segment_resource_manager);

  std::cout << "Got herei4" << endl;
  world->addEntity(segment);
  std::cout << "Got here" << endl;

  Light * light = new Light(world->m_shader, glm::vec3(0.0f, 0.0f, 9.0f));
  world->addEntity(light);

  return world;
}

int main(int argc, char** argv) {
  srand(time(NULL));

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  /* Create a windowed mode window and its OpenGL context */
  GLFWwindow * window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to initialize window" << std::endl;
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  std::cout << glGetString(GL_VERSION) << std::endl;

  // Don't show the cursor.
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Set this to true so GLEW knows to use a modern approach to retrieving
  // function pointers and extensions
  glewExperimental = GL_TRUE;

  // Initialize GLEW to setup the OpenGL Function pointers
  GLenum err = glewInit();
  std::cout << err << std::endl;

//  if (err != GLEW_OK) {
    /* Problem: glewInit failed, something is seriously wrong. */
//    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//    glfwTerminate();
//    return -1;
//  }

  // Define the viewport dimensions
  int w, h;
  glfwGetFramebufferSize(window, &w, &h);
  glViewport(0, 0, w, h);

  World * world = createWorld(window);
  std::cout << world << std::endl;


  // Set up variables for time calculations.
  GLfloat deltaTime = 0.0f;
  GLfloat timeOfLastFrame = 0.0f;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {

        // Calculate deltatime of current frame
        GLfloat timeOfCurrentFrame = glfwGetTime();
        deltaTime = timeOfCurrentFrame - timeOfLastFrame;
        timeOfLastFrame = timeOfCurrentFrame;

//        handleInput();
        world->update(deltaTime);
        world->render();


    /* Render here */
//    glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
//    glfwSwapBuffers(window);

    /* Poll for and process events */
//    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
