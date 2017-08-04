// From hws/hw2/Firework.h
// TODO: Create h and cpp file

#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>

#include "Entity.h"
#include "Shader.h"
#include "SegmentResourceManager.h"

//===========================================================
// Class : Segment
//===========================================================

class Segment : public Entity {
 public:
  Segment(Shader* shader, float radius, glm::vec3 position, float height,
        float rotation_angle, glm::vec4 color,
        SegmentResourceManager * resource_manager) {
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
  }

  ~Segment() {
    /*
            for(size_t i = 0; i < m_sparks.size(); i++) {
                Entity * curr = m_sparks.at(i);
                if (curr) delete curr;
            }
    */
  }

  void render() const;
  void update(double time_since_last_update);

 private:
  float m_radius;
  float m_height;
  float m_rotation_angle;
  SegmentResourceManager * m_resource_manager;
};

#endif
