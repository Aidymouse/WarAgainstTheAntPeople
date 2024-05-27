#include <state/CollisionManager.hpp>

#include <math.h>
#include <iostream>

bool circle_circle(Collider *s1, Collider *s2) {
  return sqrt((s1->x - s2->x) * (s1->x - s2->x) +
              (s1->y - s2->y) * (s1->y - s2->y)) <=
         s1->collisionShape.circle.radius + s2->collisionShape.circle.radius;
}

bool rect_rect(Collider *s1, Collider *s2) {
  float s1width = s1->collisionShape.rect.width;
  float s1height = s1->collisionShape.rect.height;
  float s2width = s2->collisionShape.rect.width;
  float s2height = s2->collisionShape.rect.height;
  return (s1->x <= s2->x + s2width && s1->x + s1width >= s2->x &&
          s1->y <= s2->y + s2height && s1->y + s1height >= s2->y);
}

bool circle_rect(Collider *s1, Collider *s2) {
  Collider *circle = s1->type == CollisionShapeType::CIRCLE ? s1 : s2;
  Collider *rect = s1->type == CollisionShapeType::RECT ? s1 : s2;

  float rect_width = rect->collisionShape.rect.width;
  float rect_height = rect->collisionShape.rect.height;
  float circ_radius = circle->collisionShape.circle.radius;

  float testX = circle->x;
  float testY = circle->y;
  if ( (circle->x) < (rect->x) ) testX = rect->x;
  else if ( (circle->x) > (rect->x + rect_width)) testX = rect->x + rect_width;

  if ( (circle->y) < (rect->y) ) testY = rect->y;
  else if (circle->y > rect->y + rect_height) testY = rect->y + rect_height;

  //std::cout << testX << ", " << testY << std::endl;
  float distX = circle->x - testX;
  float distY = circle->y - testY;
  float distance = sqrt( (distX*distX) + (distY*distY) );

  return distance <= circ_radius;
}

float point_dist(float p1x, float p1y, float p2x, float p2y) {
  return sqrt((p1x - p2x) * (p1x - p2x) + (p1y - p2y) * (p1y - p2y));
}

bool circle_line(Collider *s1, Collider *s2) {
  Collider *circle = s1->type == CollisionShapeType::CIRCLE ? s1 : s2;
  Collider *line = s1->type == CollisionShapeType::LINE ? s1 : s2;

  // Check if the ends are within the circle
  if (point_dist(circle->x, circle->y, line->collisionShape.line.p1x,
                 line->collisionShape.line.p1y) <=
      circle->collisionShape.circle.radius)
    return true;
  if (point_dist(circle->x, circle->y, line->collisionShape.line.p2x,
                 line->collisionShape.line.p2y) <=
      circle->collisionShape.circle.radius)
    return true;

  // Do something more complicated I forgor how. Project something ?
  return false;
}

bool CollisionManager::does_collide(Collider *s1, Collider *s2) {

  if (s1->type == CollisionShapeType::CIRCLE &&
      s2->type == CollisionShapeType::CIRCLE) {
    return circle_circle(s1, s2);

  } else if (s1->type == CollisionShapeType::CIRCLE &&
                 s2->type == CollisionShapeType::RECT ||
             s1->type == CollisionShapeType::RECT &&
                 s2->type == CollisionShapeType::CIRCLE) {
    return circle_rect(s1, s2);

  } else if (s1->type == CollisionShapeType::RECT &&
             s2->type == CollisionShapeType::RECT) {
    return rect_rect(s1, s2);
  }
  return false;
}

