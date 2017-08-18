// From hws/hw2/Firework.h

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
       SegmentResourceManager* segment_resource_manager, Camera* camera,
       GLFWwindow* window, bool is_got) {
    m_type = ET_TREE;

    m_shader = shader;
    m_pos = position;

    Segment::SegmentParams seg_params;
    seg_params.position = position;
    seg_params.height = height;
    seg_params.radius = height / 20.0;
    Segment::GenerationParams gen_params;

    if (is_got) {
      seg_params.radius = 0.5f;
      seg_params.height = 5.0f;

      gen_params.trunk_contraction_ratio = 0.6f;
      gen_params.branch_contraction_ratio = 0.6f;
      gen_params.generate_straight_segment = true;
      gen_params.num_branches = 3;
      gen_params.branch_color = glm::vec4(1.0, 1.0, 1.0, 1.0);

      gen_params.leaf_color_green = gen_params.leaf_color_red;
      gen_params.leaf_color_yellow = gen_params.leaf_color_red;
      gen_params.leaf_color_orange = gen_params.leaf_color_red;
      gen_params.leaf_color_brown = gen_params.leaf_color_red;
    }

    m_leaf_shader = new Shader(
        "/home/jen/Code/cs148/cs148-project/bin/texture.vs",
        "/home/jen/Code/cs148/cs148-project/bin/texture.frag");

    m_trunk =
        new Segment(m_shader, m_leaf_shader, segment_resource_manager,
                    seg_params, gen_params, camera, window);
  }

  ~Tree() {
    delete m_trunk;
    delete m_leaf_shader;
  }

  void render() const;
  void update(double time_since_last_update);
  void setBreezeEnabled(bool is_enabled) {
    m_trunk->setBreezeEnabled(is_enabled);
  }

 protected:
  Segment* m_trunk;
  Shader* m_leaf_shader;
};

#endif
