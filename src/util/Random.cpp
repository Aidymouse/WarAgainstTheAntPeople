#include <random>
#include <util/Random.h>

int Random::rand_range(int lower, int higher) {
  return rand() % (higher + 1 - lower) + lower;
}
