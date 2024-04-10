#include "../Types/CollisionShapes.h"

#pragma once
class CollisionManager {
public:
  static bool does_collide(CollisionShape s1, CollisionShape s2);
};
