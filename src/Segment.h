// From hws/hw2/Firework.h
// TODO: Create h and cpp file

#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>

#include "Entity.h"
#include "SegmentResourceManager.h"
#include "Shader.h"

//===========================================================
// Class : Segment
//===========================================================

class Segment : public Entity {
 public:
  Segment(Shader* shader, float radius, glm::vec3 position, float height,
          float rotation_angle, glm::vec4 color,
          SegmentResourceManager* resource_manager, int num_iterations) {
    m_type = ET_SEGMENT;

    // TODO: Replace with parent constructor?
    // Set parent class's variables.
    m_shader = shader;
    m_pos = position;
    m_color = color;

    // Set this class's variables.
    m_radius = radius;
    m_height = height;
    m_rotation_angle = rotation_angle;
    m_resource_manager = resource_manager;

    if (num_iterations > 0) {
      glm::vec3 branch_position = position;
      branch_position[0] +=
          height * cos(glm::radians<float>(90.0 + rotation_angle));
      branch_position[1] +=
          height * sin(glm::radians<float>(90.0 + rotation_angle));
      m_children.push_back(new Segment(m_shader, radius / 2.0, branch_position,
                                   height / 2.0, rotation_angle, color,
                                   resource_manager, num_iterations - 1));
      m_children.push_back(new Segment(m_shader, radius / 2.0, branch_position,
                                   height / 2.0, rotation_angle + 30.0f, color,
                                   resource_manager, num_iterations - 1));
      m_children.push_back(new Segment(m_shader, radius / 2.0, branch_position,
                                    height / 2.0, rotation_angle - 30.0f, color,
                                    resource_manager, num_iterations - 1));
    }
  }

  ~Segment() {
    for (Segment * child : m_children) {
      if (child) delete child;
    }
  }

  void render() const;
  void update(double time_since_last_update);

 private:
  float m_radius;
  float m_height;
  float m_rotation_angle;
  SegmentResourceManager* m_resource_manager;
  std::vector<Segment*> m_children;
};

#endif
