// Based on hws/hw2/Firework.h

#include "Tree.h"

void Tree::render() const { m_trunk->render(); }

void Tree::update(double time_since_last_update) {
  m_trunk->update(time_since_last_update);
}
