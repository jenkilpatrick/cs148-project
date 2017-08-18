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
  enum Phase {
    NOT_STARTED,
    GROWING,
    GREEN,
    FADE_YELLOW,
    FADE_ORANGE,
    FADE_RED,
    FADE_BROWN,
    BROWN,
    FALLING,
    FALLEN
  };

  // Configuration parameters specific to this Segment.
  struct SegmentParams {
    int level = 0;
    Type type = TRUNK;
    float radius = 0.25;
    float height = 5.0f;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 heading = glm::vec3(0.0f, 1.0f, 0.0f);
    float rotation_deg = glm::linearRand<float>(0, 360.0f);
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
    glm::vec4 leaf_color_green =
        glm::vec4(30.0f, 147.0f, 45.0f, 256.0f) / 256.0f;
    glm::vec4 leaf_color_yellow =
        glm::vec4(218.0f, 165.0f, 32.0f, 256.0f) / 256.0f;
    glm::vec4 leaf_color_orange =
        glm::vec4(210.0f, 105.0f, 30.0f, 256.0f) / 256.0f;
    // glm::vec4 leaf_color_red = glm::vec4(165.0f, 42.0f, 42.0f, 256.0f) /
    // 256.0f;
    glm::vec4 leaf_color_red = glm::vec4(218.0f, 17.0f, 0.0f, 256.0f) / 256.0f;
    glm::vec4 leaf_color_brown =
        glm::vec4(139.0f, 69.0f, 19.0f, 256.0f) / 256.0f;
    float leaf_height = 0.5f;
    float leaf_radius = 0.3f;
  };

  Segment(Shader* shader, SegmentResourceManager* resource_manager,
          SegmentParams& seg_params, GenerationParams& gen_params) {
    m_type = ET_SEGMENT;

    // TODO: Replace with parent constructor?
    // Set parent class's variables.
    m_shader = shader;
    m_params = seg_params;
    m_pos = seg_params.position;
    m_color = (seg_params.type == LEAF) ? gen_params.leaf_color_green
                                        : gen_params.branch_color;

    // TODO: Fix this setup...it's an ugly way to store these!
    m_changing_colors[0] = gen_params.leaf_color_green;
    m_changing_colors[1] = gen_params.leaf_color_yellow;
    m_changing_colors[2] = gen_params.leaf_color_orange;
    m_changing_colors[3] = gen_params.leaf_color_red;
    m_changing_colors[4] = gen_params.leaf_color_brown;

    // Set this class's variables.
    m_radius = (seg_params.type == LEAF) ? 0.0f : seg_params.radius;
    m_height = (seg_params.type == LEAF) ? 0.0f : seg_params.height;

// FOR TESTING BREEZES.
//    m_radius = seg_params.radius;
//    m_height = seg_params.height;

    m_goal_radius = seg_params.radius;
    m_goal_height = seg_params.height;
    m_initial_heading = glm::normalize(seg_params.heading);
    m_heading = m_initial_heading;
    m_resource_manager = resource_manager;

    if (seg_params.level >= gen_params.max_levels) {
      return;
    }

    if (seg_params.level == gen_params.max_levels - 1) {
      // Spawn a leaf.
      glm::vec3 branch_position = m_pos + m_height * seg_params.heading;
      SegmentParams child = seg_params;
      child.type = LEAF;
      child.radius = gen_params.leaf_radius;
      child.height = gen_params.leaf_height;
      child.position = branch_position;
      child.level += 1;
      m_children.push_back(
          new Segment(m_shader, resource_manager, child, gen_params));
      return;
    }

    glm::vec3 branch_position = m_pos + m_height * seg_params.heading;

    if (gen_params.generate_straight_segment) {
      SegmentParams child = seg_params;
      child.radius *= gen_params.width_contraction_ratio;
      child.height *= (child.type == TRUNK)
                          ? gen_params.trunk_contraction_ratio
                          : gen_params.branch_contraction_ratio;
      child.position = branch_position;
      child.level += 1;
      m_children.push_back(
          new Segment(m_shader, resource_manager, child, gen_params));
    }

    for (int i = 0; i < gen_params.num_branches; i++) {
      SegmentParams child = seg_params;
      child.radius *= 0.5f;
      child.height *= 0.5f;
      child.position = branch_position;
      child.level += 1;
      child.type = BRANCH;

      glm::vec3 rotation_axis;
      if (seg_params.type == TRUNK) {
        // TODO: Fix this to support arbitrary trunk headings.
        glm::vec3 rotation_axis = glm::vec3(0.0f, 0.0f, -1.0f);
        child.heading = glm::rotate(seg_params.heading,
                                    gen_params.branching_angle, rotation_axis);

        // If this is a branch coming off the main trunk, rotate about the
        // trunk
        // by the divergence angle.
        float divergence_angle = glm::radians(fmod(
            gen_params.divergence_angle * gen_params.num_trunk_segments_created,
            360.0f));
        gen_params.num_trunk_segments_created++;
        child.heading =
            glm::rotate(child.heading, divergence_angle, seg_params.heading);
      } else {
        glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 L = glm::normalize(glm::cross(V, seg_params.heading));
        glm::vec3 U = glm::normalize(glm::cross(seg_params.heading, L));

        float branching_angle = glm::radians(((i % 2) == 0 ? 1.0f : -1.0f) *
                                             gen_params.branching_angle);
        child.heading = glm::rotate(seg_params.heading, branching_angle, U);
      }

      m_children.push_back(
          new Segment(m_shader, resource_manager, child, gen_params));
    }
  }

  ~Segment() {
    for (Segment* child : m_children) {
      if (child) delete child;
    }
  }

  void render() const;
  void update(double time_since_last_update);
  void setBreezeEnabled(bool is_enabled) {
    m_breeze_enabled = is_enabled;
    for (Segment* child : m_children) {
      child->setBreezeEnabled(is_enabled);
    }
  }

 private:
  SegmentParams m_params;
  float m_radius;
  float m_height;

  float m_goal_radius;
  float m_goal_height;

  glm::vec3 m_initial_heading;
  glm::vec3 m_heading;

  SegmentResourceManager* m_resource_manager;
  std::vector<Segment*> m_children;

  glm::vec4 m_changing_colors[5];

  Phase m_phase = NOT_STARTED;
  float m_time_in_phase = 0.0f;

  bool m_breeze_enabled = false;
};

#endif
