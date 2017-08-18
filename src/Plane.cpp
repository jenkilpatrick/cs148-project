#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include "Plane.h"

void Plane::render() const {
  // Make sure always to set the current shader before setting
  // uniforms/drawing objects
  if (m_shader) {
    m_shader->Use();

    // Set segment color.
    GLint objectColorLoc =
        glGetUniformLocation(m_shader->Program, "objectColor");
    glUniform3f(objectColorLoc, 1.0, 1.0, 1.0);

    // Compute model matrix
    glm::mat4 output_matrix = glm::translate(glm::mat4(), m_pos);
    output_matrix = glm::translate(output_matrix, glm::vec3(0, -0.5, 0));
    output_matrix =
        glm::scale(output_matrix, glm::vec3(m_radius, 1.0, m_radius));

    // Get the locations of uniforms for the shader.
    GLint modelLoc = glGetUniformLocation(m_shader->Program, "model");

    // Pass the transformed model matrix to the shader.
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(output_matrix));

  int w, h;
  glfwGetFramebufferSize(m_window, &w, &h);

  // Set view matrix.
  glm::mat4 view = m_camera->GetViewMatrix();
  GLint view_loc = glGetUniformLocation(m_shader->Program, "view");
  glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

  // Set projection matrix.
  glm::mat4 projection =
      glm::perspective(m_camera->Zoom, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
  GLint proj_loc = glGetUniformLocation(m_shader->Program, "projection");
  glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

  }

  // Draw the cube from its VAO
  glBindTexture(GL_TEXTURE_2D, m_resource_manager->getTexture());
  glBindVertexArray(m_resource_manager->getContainerVAO());
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}

void Plane::update(double time_since_last_update) {
}
