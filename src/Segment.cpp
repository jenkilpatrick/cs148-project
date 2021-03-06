// Based on hws/hw2/Firework.h

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include <glm/gtc/random.hpp>

#include "Segment.h"

void Segment::render() const {
  // Make sure always to set the current shader before setting
  // uniforms/drawing objects
/*  if (m_params.type == LEAF) {
    m_leaf_shader->Use();
  } else {
*/    m_shader->Use();
//  }

  // Set segment color.
  GLint objectColorLoc =
      glGetUniformLocation(m_shader->Program, "objectColor");
  glUniform3f(objectColorLoc, m_color[0], m_color[1], m_color[2]);

  // Calculate relevant axes.
  glm::vec3 y_axis = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 rotation_axis = glm::normalize(glm::cross(y_axis, m_heading));
  float rotation_angle = glm::angle(y_axis, m_heading);

  // Compute model matrix
  glm::mat4 output_matrix = glm::translate(glm::mat4(), m_pos);
  if (std::abs(rotation_angle) > glm::epsilon<float>()) {
    output_matrix = glm::rotate(output_matrix, rotation_angle, rotation_axis);
  }
  output_matrix =
      glm::translate(output_matrix, glm::vec3(0.0f, m_height / 2.0f, 0.0f));
  output_matrix = glm::rotate(output_matrix,
      glm::radians(m_params.rotation_deg), y_axis);
  output_matrix =
      glm::scale(output_matrix, glm::vec3(
           (m_params.type == LEAF) ? 0.005 : m_radius, m_height, m_radius));

  // Get the locations of uniforms for the shader.
  GLint modelLoc = glGetUniformLocation(m_shader->Program, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(output_matrix));

  // Draw the cube from its VAO
/*
  if (m_params.type == LEAF) {
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

    glBindTexture(GL_TEXTURE_2D, m_resource_manager->getTexture());
    glBindVertexArray(m_resource_manager->getTextureVAO());
  } else {
*/
    glBindVertexArray(m_resource_manager->getContainerVAO());
//  }
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);

  for (Segment* child : m_children) {
    if (child) child->render();
  }
}

void Segment::update(double time_since_last_update) {
  if (m_params.type == LEAF) {
    if (m_phase != FALLEN) {
      m_time_in_phase += time_since_last_update;
    }

    double phase_length = 2.0;
    float fall_velocity = 1.0;
    glm::vec3 breeze_direction =
        glm::normalize(glm::vec3(-1.0f, 0.0f, -1.0f));
    float breeze_velocity = 0.4 + 0.3 * sin(m_time_in_phase * 2.0f);
    glm::vec3 down = glm::vec3(0.0f, -1.0f, 0.0f);

    // Update heading based on breeze.
    if (m_breeze_enabled) {
      float adjustment = 0.5f + 0.5f * sin(m_time_in_phase * 2.0f);
      m_heading = m_initial_heading + breeze_direction * adjustment;
    }

    switch (m_phase) {
      case NOT_STARTED:
        // Determine whether this leaf should start to grow.
        if (glm::linearRand<double>(0.0, 1.0) < 0.003) {
          m_phase = GROWING;
          m_time_in_phase = 0.0f;
        }
        break;
      case GROWING:
        m_height = m_goal_height * m_time_in_phase / 3.0f;
        m_radius = m_goal_radius * m_time_in_phase / 3.0f;
        if (m_height >= m_goal_height) {
          m_phase = GREEN;
          m_time_in_phase = 0.0f;
        }
        break;
      case GREEN:
        if (m_time_in_phase > 7.0) {
          // Determine whether this leaf should start to change color.
          if (m_time_in_phase > 15.0 ||
              glm::linearRand<double>(0.0, 1.0) < 0.005) {
            m_phase = FADE_YELLOW;
            m_time_in_phase = 0.0f;
          }
        }
        break;
      case FADE_YELLOW:
        // Interpolate between green and yellow.
        m_color = glm::mix(m_changing_colors[0], m_changing_colors[1],
                           std::min(1.0, m_time_in_phase / phase_length));
        if (m_time_in_phase > phase_length + 1.0) {
          m_phase = FADE_ORANGE;
          m_time_in_phase = 0.0f;
        }
        break;
      case FADE_ORANGE:
        // Interpolate between yellow and orange.
        m_color = glm::mix(m_changing_colors[1], m_changing_colors[2],
                           std::min(1.0, m_time_in_phase / phase_length));
        if (m_time_in_phase > phase_length + 1.0) {
          m_phase = FADE_RED;
          m_time_in_phase = 0.0f;
        }
        break;
      case FADE_RED:
        // Interpolate between orange and red.
        m_color = glm::mix(m_changing_colors[2], m_changing_colors[3],
                           std::min(1.0, m_time_in_phase / phase_length));
        if (m_time_in_phase > phase_length + 1.0) {
          m_phase = FADE_BROWN;
          m_time_in_phase = 0.0f;
        }
        break;
      case FADE_BROWN:
        // Interpolate between red and brown.
        m_color = glm::mix(m_changing_colors[3], m_changing_colors[4],
                           std::min(1.0, m_time_in_phase / phase_length));
        if (m_time_in_phase > phase_length + 1.0) {
          m_phase = BROWN;
          m_time_in_phase = 0.0f;
        }
        break;
      case BROWN:
        if (m_time_in_phase > 5.0) {
          // Determine whether this leaf should fall.
          if (glm::linearRand<double>(0.0, 1.0) < 0.0005) {
            m_phase = FALLING;
            m_time_in_phase = 0.0f;
          }
        }
        break;
      case FALLING:
        // Update position.
        if (m_breeze_enabled) {
          m_pos = m_pos
               + (float) time_since_last_update * fall_velocity * down
               + (float) time_since_last_update * breeze_velocity
                   * breeze_direction;
        } else {
          m_pos[1] =
              std::max(0.0, m_pos[1] - time_since_last_update * fall_velocity);
        }

        // Stop when the leaf hits the ground.
        m_pos[1] = std::max(0.0f, m_pos[1]);
        if (m_pos[1] <= 0.0) {
          m_phase = FALLEN;
          m_time_in_phase = 0.0f;
        }
        break;
      case FALLEN:
        // Do nothing.
        break;
      default:
        break;
    }
  }

  for (Segment* child : m_children) {
    if (child) child->update(time_since_last_update);
  }
}
