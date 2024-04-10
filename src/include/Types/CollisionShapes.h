#pragma once
struct CollisionCircle {
  float radius;
};

struct CollisionSquare {
  float width;
  float height;
};

struct CollisionPoint {
  float x;
  float y;
};

union CollisionShape {
  CollisionCircle circle;
  CollisionSquare square;
  CollisionPoint point;
};
