#include "Map.hpp"

void extrude(vector3 &v) {
	v.y = v.y + v.z;
	return ;
}

void rotate(vector3 &v) {
	int x = (v.x * 1) + (v.y * 1);
	int y = (v.x * 1) + (v.y * -1);

	v.x = x - (WIDTH * 1.4) / 4;
	v.y = y - (HEIGHT * 1.5) / 4;
	return ;
}

void down(vector3 &v) {
	v.y /= 2;
}
