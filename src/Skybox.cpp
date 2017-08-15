// Based on hws/hw2/Firework.h

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include "Skybox.h"

void Skybox::render() const {
  // Make sure always to set the current shader before setting
  // uniforms/drawing objects
  if (m_shader) {
    m_shader->Use();

    // Set segment color.
    GLint objectColorLoc =
        glGetUniformLocation(m_shader->Program, "objectColor");
    glUniform3f(objectColorLoc, m_color[0], m_color[1], m_color[2]);

/*
    // Calculate relevant axes.
    glm::vec3 rotation_axis = glm::normalize(glm::cross(y_axis, m_heading));
    float rotation_angle = glm::angle(y_axis, m_heading);

    // Compute model matrix
    glm::mat4 output_matrix = glm::translate(glm::mat4(), m_pos);
    if (std::abs(rotation_angle) > glm::epsilon<float>()) {
      output_matrix = glm::rotate(output_matrix, rotation_angle, rotation_axis);
    }
    output_matrix =
        glm::translate(output_matrix, glm::vec3(0.0f, m_height / 2.0f, 0.0f));
    output_matrix =
        glm::scale(output_matrix, glm::vec3(m_radius, m_height, m_radius));
*/

    float x_scaling_factor = 100.f;
    float y_scaling_factor = 100.0f;
    float z_scaling_factor = x_scaling_factor;

    glm::vec3 scale_vector = glm::vec3(
        x_scaling_factor, y_scaling_factor, z_scaling_factor);
    glm::vec3 translate_vector = glm::vec3(0.0f, y_scaling_factor / 2.0f, 0.0f);

    glm::mat4 output_matrix = glm::translate(glm::mat4(), translate_vector);
    output_matrix = glm::scale(output_matrix, scale_vector);

    // Get the locations of uniforms for the shader.
    GLint modelLoc = glGetUniformLocation(m_shader->Program, "model");

    // Pass the transformed model matrix to the shader.
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(output_matrix));
  }

  // Draw the cube from its VAO
  glBindVertexArray(m_resource_manager->getContainerVAO());
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}

void Skybox::update(double time_since_last_update) {
}
