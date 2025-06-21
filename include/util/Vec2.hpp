#pragma once

#include <cmath>
#include <iostream>

class Vec2 {

public:
  float x;
  float y;

  Vec2(float x_in, float y_in) {
    x = x_in;
    y = y_in;
  };

  Vec2() { Vec2(0, 0); };

  // Assume 0 is upwards (0, -1)
  void face_angle(float degrees) {
    float mag = this->get_magnitude();
    float dir_x = sin(degrees);
    float dir_y = -cos(degrees);
    x = dir_x * mag;
    y = dir_y * mag;
  };

  void operator=(Vec2 a) {
    x = a.x;
    y = a.y;
  }

  /** Addition and assignmnet += */
  Vec2 &operator+=(Vec2 rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  };
  Vec2 &operator+=(float rhs) {
    x += rhs;
    y += rhs;
    return *this;
  };

  /** Addition + */
  friend Vec2 operator+(Vec2 lhs, const Vec2 &rhs) {
    return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
  };
  friend Vec2 operator+(Vec2 lhs, const float &rhs) {
    return Vec2(lhs.x + rhs, lhs.y + rhs);
  };
  friend Vec2 operator+(const float &lhs, Vec2 rhs) {
    return Vec2(lhs + rhs.x, lhs + rhs.y);
  };

  /** Subtraction + */
  friend Vec2 operator-(Vec2 lhs, const Vec2 &rhs) {
    return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
  };
  friend Vec2 operator-(Vec2 lhs, const float &rhs) {
    return Vec2(lhs.x - rhs, lhs.y - rhs);
  };

  /** Times * */
  friend Vec2 operator*(Vec2 lhs, const float &rhs) {
    return Vec2(lhs.x * rhs, lhs.y * rhs);
  };
  friend Vec2 operator*(const float &lhs, Vec2 rhs) {
    return Vec2(lhs * rhs.x, lhs * rhs.y);
  };

  float get_magnitude() { return sqrt(x * x + y * y); }

  /** Normalization */
  void normalize() {
    float mag = get_magnitude();
    x /= mag;
    y /= mag;
  }

  Vec2 normalized() {
    float mag = get_magnitude();
    return Vec2(x / mag, y / mag);
  }

  // TODO: dot product or smn. DONT CARE!
};
