#pragma once
struct CollisionCircle {
  float radius;
};

struct CollisionRect {
  float width;
  float height;
};

struct CollisionLine {
  float p1x;
  float p1y;
  float p2x;
  float p2y;
};

union CollisionShape {
  CollisionCircle circle;
  CollisionRect rect;
  CollisionLine line;
};

enum CollisionShapeType { CIRCLE, RECT, LINE };

struct Collider {
  CollisionShapeType type;
  float x;
  float y;
  CollisionShape collisionShape;
};
