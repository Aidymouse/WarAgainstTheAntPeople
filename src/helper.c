#include "helper.h"

#include <stdlib.h>
#include <stdio.h>
#include "helper.h"
#include "raylib.h"
#include <math.h>

int randInt(int lower, int upper) {
	return rand() % (upper - lower + 1) + lower;
}
