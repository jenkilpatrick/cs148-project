// From hws/hw2/Firework.h

#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "Entity.h"
#include "SegmentResourceManager.h"
#include "Shader.h"

//===========================================================
// Class : Segment
//===========================================================

class Segment : public Entity {
 public:
  enum Type { TRUNK, BRANCH, LEAF };

  // Configuration parameters specific to this Segment.
  struct SegmentParams {
    int level = 0;
    Type type = TRUNK;
    float radius = 0.25;
    float height = 5.0f;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 heading = glm::vec3(0.0f, 1.0f, 0.0f);
  };

  // Configuration parameters for generating new Segments.
  struct GenerationParams {
    // The number of recursive levels of branches to generate.
    int max_levels = 7;

    // Branching behavior.
    bool generate_straight_segment = true;
    int num_branches = 2;
    glm::vec4 branch_color = glm::vec4(205.0f, 133.0f, 63.0f, 256.0f) / 256.0f;
    float branching_angle = 45.0f;
    float divergence_angle = 137.5f;
    int num_trunk_segments_created = 0;

    // Contraction ratios.
    float trunk_contraction_ratio = 0.9f;
    float branch_contraction_ratio = 0.6f;
    float width_contraction_ratio = 0.707f;

    // Leaf configuration params.
    bool generate_leaves = true;
    glm::vec4 leaf_color = glm::vec4(30.0f, 147.0f, 45.0f, 256.0f) / 256.0f;
    float leaf_height = 0.5f;
    float leaf_radius = 0.3f;
  };

  Segment(Shader* shader, SegmentResourceManager* resource_manager,
          SegmentParams& segParams, GenerationParams& genParams) {
    m_type = ET_SEGMENT;

    // TODO: Replace with parent constructor?
    // Set parent class's variables.
    m_shader = shader;
    m_pos = segParams.position;
    m_color = (segParams.type == LEAF) ? genParams.leaf_color
                                       : genParams.branch_color;

    // Set this class's variables.
    m_radius = segParams.radius;
    m_height = segParams.height;
    m_heading = glm::normalize(segParams.heading);
    m_resource_manager = resource_manager;

    if (segParams.level > genParams.max_levels) {
      return;
    }

    if (segParams.level == genParams.max_levels) {
      // Spawn a leaf.
      glm::vec3 branch_position = m_pos + m_height * segParams.heading;
      SegmentParams child = segParams;
      child.type = LEAF;
      child.radius = genParams.leaf_radius;
      child.height = genParams.leaf_height;
      child.position = branch_position;
      child.level += 1;
      m_children.push_back(
          new Segment(m_shader, resource_manager, child, genParams));
      return;
    }

    glm::vec3 branch_position = m_pos + m_height * segParams.heading;

    if (genParams.generate_straight_segment) {
      SegmentParams child = segParams;
      child.radius *= genParams.width_contraction_ratio;
      child.height *= (child.type == TRUNK)
                          ? genParams.trunk_contraction_ratio
                          : genParams.branch_contraction_ratio;
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
      child.type = BRANCH;

      glm::vec3 rotation_axis;
      if (segParams.type == TRUNK) {
        // TODO: Fix this to support arbitrary trunk headings.
        glm::vec3 rotation_axis = glm::vec3(0.0f, 0.0f, -1.0f);
        child.heading = glm::rotate(segParams.heading,
                                    genParams.branching_angle, rotation_axis);

        // If this is a branch coming off the main trunk, rotate about the
        // trunk
        // by the divergence angle.
        float divergence_angle = glm::radians(fmod(
            genParams.divergence_angle * genParams.num_trunk_segments_created,
            360.0f));
        genParams.num_trunk_segments_created++;
        child.heading =
            glm::rotate(child.heading, divergence_angle, segParams.heading);
      } else {
        glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 L = glm::normalize(glm::cross(V, segParams.heading));
        glm::vec3 U = glm::normalize(glm::cross(segParams.heading, L));

        float branching_angle = glm::radians(((i % 2) == 0 ? 1.0f : -1.0f) *
                                             genParams.branching_angle);
        child.heading = glm::rotate(segParams.heading, branching_angle, U);
      }

      m_children.push_back(
          new Segment(m_shader, resource_manager, child, genParams));
    }
  }

  ~Segment() {
    for (Segment* child : m_children) {
      if (child) delete child;
    }
  }

  void render() const;
  void update(double time_since_last_update);

 private:
  float m_radius;
  float m_height;
  glm::vec3 m_heading;
  SegmentResourceManager* m_resource_manager;
  std::vector<Segment*> m_children;
};

#endif
