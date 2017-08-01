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
  World(GLFWwindow *window) {
    std::cout << "end of world" << endl;
    m_window = window;
#ifdef WIN32
    std::cout << "end of world" << endl;
    m_shader = new Shader("../phong.vs", "../phong.frag");
#else
    std::cout << "end of world2" << endl;
    m_shader = new Shader("/home/jen/Code/cs148/cs148-project/bin/phong.vs",
                          "/home/jen/Code/cs148/cs148-project/bin/phong.frag");
#endif
    std::cout << "end of world" << endl;
    m_camera = new Camera(glm::vec3(0.0f, 0.0f, 14.0f));
    std::cout << "end of world" << endl;
  }

  ~World() {
    for (size_t i = 0; i < m_entities.size(); i++) {
      Entity *curr = m_entities.at(i);
      if (curr) delete curr;
    }

    if (m_shader) delete m_shader;
    if (m_camera) delete m_camera;
  }

  void addEntity(Entity * entity);
  void render() const;
  void update(double time_since_last_update);

  Shader * m_shader;
  Camera * m_camera;

 private:
  GLFWwindow * m_window;
  vector<Entity *> m_entities;

  void handleCollisions(Entity * entity);
};

#endif
