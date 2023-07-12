#include "Map.hpp"

void extrude(vector3 &v) {
	v.y = v.y + v.z;
	return ;
}

void rotate(vector3 &v) {
	v.x = std::round((v.x - v.y) / std::sqrt(2));
	v.y = std::round((v.x + v.y) / std::sqrt(2));
	return ;
}

void down(vector3 &v) {
	v.y /= 1.2;
}
