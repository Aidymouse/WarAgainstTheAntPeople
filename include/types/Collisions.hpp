#pragma once
class Entity;

struct explosion_collision {
  float distance;
  float bomb_pos_x;
  float bomb_pos_y;
  float blast_strength_high;
  float blast_strength_far;
};

union collision_data {
  explosion_collision explosion;
};

enum Collisions { MALLET, EXPLOSION };

struct Collision {
  Collisions type;
  Entity *collided_with;
  collision_data data;
};
