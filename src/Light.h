// From hws/hw2/Light.h

#ifndef ENTITY_H
#define ENTITY_H

#include "Entity.h"

class Entity;

//===========================================================
// Class : Light
//===========================================================

class Light : public Entity {
 public:
  Light(Shader* shader, glm::vec3 initial_pos) {
    m_type = ET_LIGHT;
    m_shader = shader;
    m_initial_pos = initial_pos;
    m_pos = initial_pos;
  }

  ~Light() {}

  void render() const;
  void update(double time_since_last_update);
  void toggleBlue();
  void toggleRotation();

 protected:
  glm::vec3 m_initial_pos;
  bool m_is_blue = false;
  bool m_rotate = false;
  int m_theta_deg = 0;
};

#endif
