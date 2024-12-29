#pragma once

enum CollisionShapeType {
	RECT,
	CIRCLE
};

struct CollisionRect {
	CollisionShapeType type = CollisionShapeType::RECT;
	int x;
	int y;
	int width;
	int height;
};

struct CollisionCircle {
	CollisionShapeType type = CollisionShapeType::CIRCLE;
	int x;
	int y;
	int radius;
};

union CollisionShape {
	CollisionRect rect;
	CollisionCircle circle;
};

namespace Collisions {
	bool circle_rect(CollisionCircle circle, CollisionRect rect);
	bool rect_rect(CollisionRect rect1, CollisionRect rect2);
	bool circle_circle(CollisionCircle circle1, CollisionCircle circle2);
}
