#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

const float ε = 0.0001;

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
    float dir_x = sin(degrees * 0.01745329);
    float dir_y = -cos(degrees * 0.01745329);
    x = dir_x * mag;
    y = dir_y * mag;

    if (std::abs(x) < ε)
      x = 0;
    if (std::abs(y) < ε)
      y = 0;
  };

  float get_angle_facing() { return tanh(y / x) / 0.01745329; }

  operator std::string() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
  }

  friend std::ostream &operator<<(std::ostream &, Vec2 &a) {
    std::cout << "(" + std::to_string(a.x) + ", " + std::to_string(a.y) + ")";
    return std::cout;
  }

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

  /** Helper */
  void cout() { std::cout << x << ", " << y; }
};
