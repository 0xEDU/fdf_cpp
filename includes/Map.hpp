#pragma once
#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

typedef std::pair<int, int> position;

class Map {
	private:
		std::map<position, int> _map;

	public:
		Map();
		~Map();

		void loadMap(char *mapFile);
};

#endif // !MAP_HPP
