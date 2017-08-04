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
//    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

    // Compute model matrix
    glm::mat4 scaled_matrix = glm::scale(
        glm::mat4(), glm::vec3(m_radius, m_height, 1.0f));
    glm::mat4 output_matrix = glm::translate(scaled_matrix, m_pos);

    // TODO: Allow segment to be rotated.

/*
    glm::mat4 rotatedCubeModelMat4 = glm::rotate(
        glm::mat4(), m_global_rotation_theta_deg * glm::pi<float>() / 180.0f,
        up);
    glm::mat4 translatedCubeModelMat4 =
        glm::translate(rotatedCubeModelMat4, glm::vec3(m_pos));
    glm::mat4 translatedScaledCubeModelMat4 =
        glm::scale(translatedCubeModelMat4,
                   glm::vec3(m_size_scaling_factor * m_current_breath_amt));
    glm::mat4 translatedScaledRotatedCubeModelMat4 =
        glm::rotate(translatedScaledCubeModelMat4,
                    m_local_rotation_theta_deg * glm::pi<float>() / 180.0f, up);
*/

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
