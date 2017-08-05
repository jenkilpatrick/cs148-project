// From hws/hw2/Firework.h
// TODO: Create h and cpp file

#ifndef TREE_H
#define TREE_H

#include <vector>

#include "Entity.h"
#include "Segment.h"
#include "SegmentResourceManager.h"

//===========================================================
// Class : Tree
//===========================================================

class Tree : public Entity {
 public:
  Tree(Shader* shader, glm::vec3 position,
       SegmentResourceManager* segment_resource_manager) {
    m_type = ET_TREE;

    m_shader = shader;
    m_pos = position;

    // Add objects to the world.
//    float radius = 1.0f;
//    float height = 5.0f;
//    float rotation_angle = 0.0f;
//    glm::vec4 color = glm::vec4(205.0f, 133.0f, 63.0f, 256.0f) / 256.0f;

    Segment::SegmentParams segParams;
    Segment::GenerationParams genParams;
    m_trunk = new Segment(m_shader, segment_resource_manager, segParams, genParams);
  }

  ~Tree() { delete m_trunk; }

  void render() const;
  void update(double time_since_last_update);

 protected:
  Segment* m_trunk;
};

#endif
