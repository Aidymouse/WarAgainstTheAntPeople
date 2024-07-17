#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>


class Helper {
public:
	static float dist_tween_points(float x1, float y1, float x2, float y2) {

		return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
			
	}
	static int random(int low, int high) {
		return rand() % (high + 1 - low) + low;
	}
	static void normalize_vec2(sf::Vector2<float>* v) {
		float v_mag = sqrtf(v->x *v->x+v->y*v->y );
		v->x /= v_mag;
		v->y /= v_mag;
	}

	static void normalize_vec3(sf::Vector3<float>* v) {
		float v_mag = sqrtf(v->x*v->x + v->y*v->y + v->z*v->z);
		v->x /= v_mag;
		v->y /= v_mag;
		v->z /= v_mag;
	}
};
