#pragma once

#include <inttypes.h>

typedef int16_t coord_t;

struct Point {
    coord_t x;
    coord_t y;
    coord_t z;

    Point(coord_t x_c, coord_t y_c, coord_t z_c): x(x_c), y(y_c), z(z_c) {};
    Point(): x(0), y(0), z(0) {};
};