#include "../include/Lib/CollisionManager.h"

#include <math.h>

bool CollisionManager::does_collide(Collider *s1, Collider *s2) {

  // Circle Circle
  if (s1->type == CollisionShapeType::CIRCLE &&
      s2->type == CollisionShapeType::CIRCLE) {
    return sqrt((s1->x - s2->x) * (s1->x - s2->x) +
                (s1->y - s2->y) * (s1->y - s2->y)) <=
           s1->collisionShape.circle.radius + s2->collisionShape.circle.radius;

    // Rect - Circle (primitavely treats circle as rectangle)
  } else if (s1->type == CollisionShapeType::CIRCLE &&
                 s2->type == CollisionShapeType::RECT ||
             s1->type == CollisionShapeType::RECT &&
                 s2->type == CollisionShapeType::CIRCLE) {

    Collider *circle = s1->type == CollisionShapeType::CIRCLE ? s1 : s2;
    Collider *rect = s1->type == CollisionShapeType::RECT ? s1 : s2;

    float rect_width = rect->collisionShape.square.width;
    float rect_height = rect->collisionShape.square.height;
    float circ_radius = circle->collisionShape.circle.radius;
    float circ_x = circle->x - circ_radius / 2;
    float circ_y = circle->y - circ_radius / 2;

    return (
        circ_x <= rect->x + rect_width && circ_x + circ_radius * 2 >= rect->x &&
        circ_y <= rect->y + rect_height && circ_y + circ_radius * 2 >= rect->y);

    // Rect - Rect
  } else if (s1->type == CollisionShapeType::RECT &&
             s2->type == CollisionShapeType::RECT) {
    float s1width = s1->collisionShape.square.width;
    float s1height = s1->collisionShape.square.height;
    float s2width = s2->collisionShape.square.width;
    float s2height = s2->collisionShape.square.height;
    return (s1->x <= s2->x + s2width && s1->x + s1width >= s2->x &&
            s1->y <= s2->y + s2height && s1->y + s1height >= s2->y);
  }
  return false;
}
