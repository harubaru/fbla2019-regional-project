#include "aabb.h"

bool aabb_point_intersect(Vector2 point, Rectangle box)
{
	float xmin = box.x;
	float xmax = box.x + box.width;
	float ymin = box.y;
	float ymax = box.y + box.height;

	return (point.x >= xmin && point.x <= xmax) && (point.y >= ymin && point.y <= ymax);
}

bool aabb_quad_intersect(Rectangle a, Rectangle b)
{
	float xmin1 = a.x;
	float xmax1 = a.x + a.width;
	float ymin1 = a.y;
	float ymax1 = a.y + a.height;

	float xmin2 = b.x;
	float xmax2 = b.x + b.width;
	float ymin2 = b.y;
	float ymax2 = b.y + b.height;
	
	return (xmin1 <= xmax2 && xmax1 >= xmin2) && (ymin1 <= ymax2 && ymax1 >= ymin2);
}
