#ifndef AABB_H
#define AABB_H

#include <raylib.h>

bool aabb_point_intersect(Vector2 point, Rectangle box);
bool aabb_quad_intersect(Rectangle a, Rectangle b);

#endif