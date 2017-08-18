#ifndef PLANE_H
#define PLANE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "Camera.h"
#include "Entity.h"
#include "PlaneResourceManager.h"
#include "Shader.h"

//===========================================================
// Class : Plane
//===========================================================

class Plane : public Entity {
 public:
  Plane(Shader* shader, Camera* camera, GLFWwindow* window) {
    m_type = ET_PLANE;
    m_shader = shader;

    m_shader = new Shader(
        "/home/jen/Code/cs148/cs148-project/bin/texture.vs",
        "/home/jen/Code/cs148/cs148-project/bin/texture.frag");

    m_pos = glm::vec3(0, 0, 0);
    m_color = glm::vec4(0.17, 0.7, 0.17, 1.0);


    m_camera = camera;
    m_window = window;
    m_radius = 1000.0;
    m_resource_manager = new PlaneResourceManager();;
  }

  ~Plane() {
    if (m_resource_manager) delete m_resource_manager;
    if (m_shader) delete m_shader;
  }

  void render() const;
  void update(double time_since_last_update);

 private:
  float m_radius;
  PlaneResourceManager* m_resource_manager;
  Camera * m_camera;
  GLFWwindow * m_window;
};

#endif
