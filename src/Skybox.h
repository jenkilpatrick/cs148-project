#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Entity.h"
#include "Shader.h"
#include "SkyboxResourceManager.h"

//===========================================================
// Class : Skybox
//===========================================================

class Skybox : public Entity {
 public:
  Skybox(Shader * shader, Camera * camera, GLFWwindow * window) {
    m_type = ET_SKYBOX;

    // TODO: Replace with parent constructor?
    // Set parent class's variables.
    m_shader = shader;
    m_pos = glm::vec3(0.0, 0.0, 0.0);
    m_color = glm::vec4(0.7, 0.17, 0.17, 1.0);

    m_camera = camera;
    m_window = window;
    m_resource_manager = new SkyboxResourceManager();
  }

  ~Skybox() {
    if (m_resource_manager) delete m_resource_manager;
  }

  void render() const;
  void update(double time_since_last_update);

 private:
  SkyboxResourceManager* m_resource_manager;
  Camera * m_camera;
  GLFWwindow * m_window;
};

#endif
