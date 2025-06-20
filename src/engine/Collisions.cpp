
#include <cmath>
#include <components/Components.hpp>
#include <engine/Collisions.h>

void Collisions::update_collider_position(Collider *col, float x, float y) {
  if (col->type == CollisionShapeType::CIRCLE) {
    col->shape.circle.x = x;
    col->shape.circle.y = y;
  } else if (col->type == CollisionShapeType::RECT) {
    col->shape.rect.x = x;
    col->shape.rect.x = y;
  }
}

bool Collisions::collision(Collider col1, Collider col2) {
  if (col1.type == CollisionShapeType::CIRCLE &&
      col2.type == CollisionShapeType::CIRCLE) {
    return Collisions::circle_circle(col1.shape.circle, col2.shape.circle);
  }

  return false;
};

bool Collisions::circle_circle(CollisionCircle circle1,
                               CollisionCircle circle2) {
  // std::cout << "Circle Collision"
  //  std::cout << "Colliding between circles: (" << circle1.x << ", " <<
  //  circle1.y << ", " << circle1.radius << ") - (" << circle2.x << ", " <<
  //  circle2.y << ", " << circle2.radius << ")" << std::endl;
  int dist_x = circle1.x - circle2.x;
  int dist_y = circle1.y - circle2.y;
  return dist_x * dist_x + dist_y * dist_y <=
         (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);
}
