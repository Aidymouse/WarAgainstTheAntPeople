#pragma once

struct Collider; // Forward declare

enum CollisionShapeType { RECT, CIRCLE };

struct CollisionRect {
  float x;
  float y;
  float width;
  float height;
};

struct CollisionCircle {
  float x;
  float y;
  float radius;
};

union CollisionShape {
  CollisionRect rect;
  CollisionCircle circle;
};

namespace Collisions {
bool collision(Collider col1, Collider col2);
bool circle_rect(CollisionCircle circle, CollisionRect rect);
bool rect_rect(CollisionRect rect1, CollisionRect rect2);
bool circle_circle(CollisionCircle circle1, CollisionCircle circle2);
} // namespace Collisions
