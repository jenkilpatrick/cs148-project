// Based on hws/hw2/Firework.h

#include "Segment.h"

void Segment::render() const {
  // Render a segment as a basic cylinder.

  // Make sure always to set the current shader before setting
  // uniforms/drawing objects
  if (m_shader) {
    m_shader->Use();

    // Set segment color.
    GLint objectColorLoc =
        glGetUniformLocation(m_shader->Program, "objectColor");
    glUniform3f(objectColorLoc, m_color[0], m_color[1], m_color[2]);

    // Calculate relevant vertical axes.
//    glm::vec3 x_axis = glm::vec3(1.0f, 0.0f, 0.0f);
//    glm::vec3 y_axis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 z_axis = glm::vec3(0.0f, 0.0f, 1.0f);

    // Compute model matrix
    glm::mat4 translated_matrix = glm::translate(glm::mat4(), m_pos);
    glm::mat4 rotated_matrix = glm::rotate(translated_matrix,
        m_rotation_angle * glm::pi<float>() / 180.0f, z_axis);
    glm::mat4 output_matrix = glm::scale(
        rotated_matrix, glm::vec3(m_radius, m_height, m_radius));

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

void Segment::update(double time_since_last_update) {}
