#include <types/CollisionShapes.hpp>

#pragma once
class CollisionManager {
public:
  static bool does_collide(Collider *s1, Collider *s2);
};
