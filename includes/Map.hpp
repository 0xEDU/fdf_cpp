#pragma once
#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

#include "Mlx.hpp"

#define WIDTH 1280
#define HEIGHT 800

class Map {
	private:
		std::map<int, vector3>	_map;
		int						_rows;
		int						_cols;
		
		void isometricRender(void);
		void transformMap(void (*transformation)(vector3 &));
		void writeMapToImage(Mlx &);

	public:
		Map();
		~Map();

		void renderMap(Mlx &mlx);
		void loadMap(char *mapFile);

		std::map<int, vector3> &getMap(void);
};

std::ostream &operator<<(std::ostream &o, std::map<int, vector3> &map);
std::ostream &operator<<(std::ostream &o, vector3 &v);

void extrude(vector3 &v);
void rotate(vector3 &v);
void down(vector3 &v);

#endif // !MAP_HPP
