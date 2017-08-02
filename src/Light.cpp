// From hws/hw2/Light.h

#include "Light.h"

void Light::render() const {
  if (m_shader) {
    m_shader->Use();

    GLint lightColorLoc = glGetUniformLocation(m_shader->Program, "lightColor");
    GLint lightPosLoc = glGetUniformLocation(m_shader->Program, "lightPos");

    // pass data to the shader's variables
    glUniform3f(lightColorLoc, m_color[0], m_color[1], m_color[2]);
    glUniform3f(lightPosLoc, m_pos.x, m_pos.y, m_pos.z);
  }
}

void Light::toggleBlue() { m_is_blue = !m_is_blue; }

void Light::toggleRotation() {
  m_rotate = !m_rotate;
  if (m_rotate) {
    m_theta_deg = 0;
  } else {
    m_pos = m_initial_pos;
  }
}

void Light::update(double time_since_last_update) {
  // Set color to white or blue.
  m_color = glm::vec4(m_is_blue ? 0.0 : 1.0, m_is_blue ? 0.0 : 1.0, 1.0, 1.0);

  // Set position appropriately.
  if (m_rotate) {
    // Update theta
    double rotation_speed = 120.0;
    m_theta_deg += floor(time_since_last_update * rotation_speed);
    m_theta_deg = m_theta_deg % 360;

    // Update position
    double pi = 3.14159265359;
    double radius = 5.0;
    m_pos = glm::vec3(radius * cos(-m_theta_deg * pi / 180.0),
                      radius * sin(-m_theta_deg * pi / 180.0), m_pos[2]);
  }
}
