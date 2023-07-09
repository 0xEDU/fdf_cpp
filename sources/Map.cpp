#include "Map.hpp"

Map::Map() : _map(std::map<position, int>()) {
	return ;
}

Map::~Map() {
	return ;
}

void Map::loadMap(char *mapFile) {
	std::ifstream			input(mapFile);
	std::string				line;
	int						x = 0, y = 0;

	while (std::getline(input, line)) {
		std::istringstream iss(line);
		int z;

		y = 0;
		while (iss >> z) {
			position pos(x, y);

			this->_map.insert(std::make_pair(pos, z));
			char whitespace;
			iss >> whitespace;
			y++;
		}
		x++;
	}
	return ;
}
