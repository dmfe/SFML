#include <algorithm>
#include <cassert>

#include "SceneNode.hpp"
#include "Foreach.hpp"

SceneNode::SceneNode() : children(), parent(nullptr) {}

void SceneNode::attachChild(Ptr child) {

  child->parent = this;
  children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node) {

  auto found = std::find_if(children.begin(), children.end(),
                            [&](Ptr &p) { return p.get() == &node; });
  assert(found != children.end());

  Ptr result = std::move(*found);
  result->parent = nullptr;
  children.erase(found);

  return result;
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {

  // Apply transform of the current node
  states.transform *= getTransform();

  // Draw node and children nodes with changed transform
  drawCurrent(target, states);
  drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget &target,
                            sf::RenderStates states) const {
  // Nothing to do by default
}

void SceneNode::drawChildren(sf::RenderTarget &target,
                             sf::RenderStates states) const {
  FOREACH(const Ptr& child, children) {
    child->draw(target, states);
  }
}

void SceneNode::update(sf::Time dt) {
  updateCurrent(dt);
  updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt) {
  // Nothing to do by default
}

void SceneNode::updateChildren(sf::Time dt) {
  FOREACH(const Ptr& child, children) {
    child->update(dt);
  }
}

sf::Vector2f SceneNode::getWorldPosition() const {
  return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const {
  sf::Transform transform = sf::Transform::Identity;

  for (const SceneNode* node = this; node != nullptr; node = node->parent) {
    transform = node->getTransform() * transform;
  }

  return transform;
}

