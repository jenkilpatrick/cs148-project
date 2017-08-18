// From hws/hw2/World.h

#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include <GLFW/glfw3.h>

// GLM Mathematics
#define GLM_FORCE_RADIANS  // force everything in radian
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Shader.h"

using namespace std;

//===========================================================
// Class : World
// The entire world in which all entities exist
//===========================================================

class World {
 public:
  World(GLFWwindow* window) {
    m_window = window;
#ifdef WIN32
    m_shader = new Shader("../phong.vs", "../phong.frag");
#else
        cout << "M" << endl;
    m_shader = new Shader("/home/jen/Code/cs148/cs148-project/bin/phong.vs",
                          "/home/jen/Code/cs148/cs148-project/bin/phong.frag");
        cout << "M" << endl;
    m_skybox_shader = new Shader(
                          "/home/jen/Code/cs148/cs148-project/bin/skybox.vs",
                          "/home/jen/Code/cs148/cs148-project/bin/skybox.frag");
#endif
    m_camera = new Camera(glm::vec3(0.0f, 12.0f, 23.0f));
  }

  ~World() {
    for (size_t i = 0; i < m_entities.size(); i++) {
      Entity* curr = m_entities.at(i);
      if (curr) delete curr;
    }

    if (m_shader) delete m_shader;
    if (m_skybox_shader) delete m_skybox_shader;
    if (m_camera) delete m_camera;
  }

  void addEntity(Entity* entity);
  void render() const;
  void update(double time_since_last_update);
  void togglePause();
  void toggleBreeze();

  Shader* m_shader;
  Shader* m_skybox_shader;
  Camera* m_camera;

 private:
  GLFWwindow* m_window;
  vector<Entity*> m_entities;
  bool m_is_paused = false;
  bool m_breeze_enabled = false;

  void handleCollisions(Entity* entity);
};

#endif
