#pragma once
struct CollisionCircle {
  float radius;
};

struct CollisionSquare {
  float width;
  float height;
};

union CollisionShape {
  CollisionCircle circle;
  CollisionSquare square;
};

enum CollisionShapeType {
  CIRCLE,
  RECT,
};

struct Collider {
  CollisionShapeType type;
  float x;
  float y;
  CollisionShape collisionShape;
};
