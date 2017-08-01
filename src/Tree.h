// From hws/hw2/Firework.h
// TODO: Create h and cpp file

#ifndef TREE_H
#define TREE_H

#include <vector>

class Entity;
class ResourceManager;

//===========================================================
// Class : Tree
//===========================================================

class Tree : public Entity {
 public:
  Tree(Shader* shader, int num_sparks, float initial_radius,
       glm::vec3 initial_pos, glm::vec4 initial_color) {
    m_type = ET_FIREWORK;

    m_shader = shader;
    m_pos = initial_pos;

    m_initial_radius = initial_radius;
    m_radius = initial_radius;

    m_total_time = 0.0;
    m_random_delta = 0.5 * (m_pos.x + m_pos.y + m_pos.z);

    m_initial_color = initial_color;
    m_color = m_initial_color;
  }

  ~Tree() {
    /*
            for(size_t i = 0; i < m_sparks.size(); i++) {
                Entity * curr = m_sparks.at(i);
                if (curr) delete curr;
            }
    */
  }

  void render() const;
  void update(double time_since_last_update);

 protected:
  float m_current_breath_amt;
  float m_initial_radius;
  float m_radius;
  glm::vec4 m_initial_color;

  bool m_global_rotation = false;
  bool m_local_rotation = false;
  int m_global_rotation_theta_deg = 0;
  int m_local_rotation_theta_deg = 0;

  GLfloat m_random_delta;
};

#endif
