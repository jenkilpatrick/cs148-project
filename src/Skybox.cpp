#include "Skybox.h"

void Skybox::render() const {

  glDepthFunc(GL_LEQUAL);
  m_shader->Use();

  int w, h;
  glfwGetFramebufferSize(m_window, &w, &h);

  // Set view matrix.
  glm::mat4 view = glm::mat4(glm::mat3(m_camera->GetViewMatrix()));
  GLint view_loc = glGetUniformLocation(m_shader->Program, "view");
  glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

  // Set projection matrix.
  glm::mat4 projection =
      glm::perspective(m_camera->Zoom, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
  GLint proj_loc = glGetUniformLocation(m_shader->Program, "projection");
  glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

  // Render the skybox.
  glBindVertexArray(m_resource_manager->getContainerVAO());
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, m_resource_manager->getTexture());
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
  glDepthFunc(GL_LESS);
}

void Skybox::update(double time_since_last_update) {}
