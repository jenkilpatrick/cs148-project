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
  Tree(Shader* shader, glm::vec3 position, float height,
       SegmentResourceManager* segment_resource_manager) {
    m_type = ET_TREE;

    m_shader = shader;
    m_pos = position;

    Segment::SegmentParams seg_params;
    seg_params.position = position;
    seg_params.height = height;
    seg_params.radius = height / 20.0;
    Segment::GenerationParams gen_params;

    m_trunk =
        new Segment(m_shader, segment_resource_manager, seg_params, gen_params);
  }

  ~Tree() { delete m_trunk; }

  void render() const;
  void update(double time_since_last_update);
  void setBreezeEnabled(bool is_enabled) {
    m_trunk->setBreezeEnabled(is_enabled);
  }

 protected:
  Segment* m_trunk;
};

#endif
