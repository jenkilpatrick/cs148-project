// From hws/hw2/Firework.h

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
// Configuration parameters specific to this Segment.
struct SegmentParams {
  int level = 0;
  float radius = 0.5;
  float height = 5.0f;
  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
  float rotation_angle = 0.0f;
  glm::vec4 color = glm::vec4(205.0f, 133.0f, 63.0f, 256.0f) / 256.0f;
};

// Configuration parameters for generating new Segments.
struct GenerationParams {
  int max_levels = 2;
  bool generate_straight_segment = true;
  int num_branches = 2;
  float divergence_angle = 60.0f;
};

  Segment(Shader* shader, SegmentResourceManager* resource_manager,
      SegmentParams& segParams, GenerationParams& genParams) {
    m_type = ET_SEGMENT;

    // TODO: Replace with parent constructor?
    // Set parent class's variables.
    m_shader = shader;
    m_pos = segParams.position;
    m_color = segParams.color;

    // Set this class's variables.
    m_radius = segParams.radius;
    m_height = segParams.height;
    m_rotation_angle = segParams.rotation_angle;
    m_resource_manager = resource_manager;

    if (segParams.level < genParams.max_levels) {
      glm::vec3 branch_position = m_pos;
      branch_position[0] +=
          m_height * cos(glm::radians<float>(90.0 + m_rotation_angle));
      branch_position[1] +=
          m_height * sin(glm::radians<float>(90.0 + m_rotation_angle));

      if (genParams.generate_straight_segment) {
        SegmentParams child = segParams;
        child.radius *= 0.5f;
        child.height *= 0.5f;
        child.position = branch_position;
        child.level += 1;
        m_children.push_back(
            new Segment(m_shader, resource_manager, child, genParams));
      }

      for (int i = 0; i < genParams.num_branches; i++) {
        SegmentParams child = segParams;
        child.radius *= 0.5f;
        child.height *= 0.5f;
        child.position = branch_position;
        child.level += 1;
        child.rotation_angle +=
            ((i % 2) == 0 ? 1.0f : -1.0f) * genParams.divergence_angle;
        m_children.push_back(
            new Segment(m_shader, resource_manager, child, genParams));
      }
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
