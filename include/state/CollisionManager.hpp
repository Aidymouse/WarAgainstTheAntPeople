#pragma once
#include <types/CollisionShapes.hpp>

class CollisionManager {
public:
  static bool does_collide(Collider *s1, Collider *s2);
};
