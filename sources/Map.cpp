#include "Map.hpp"
#include <mlx.h>

/* Default builders ========================================================= */
Map::Map() : _map(std::map<position, int>()) {
	return ;
}

Map::~Map() {
	return ;
}
/* ========================================================================== */

// std::ostream &operator<<(std::ostream &o, std::map<position, int> &map) {
// 	for (auto i : map) {
// 		o << "x = " << i.first.first
// 			<< " | y = " << i.first.second
// 			<< " | z = " << i.second
// 			<< std::endl;
// 	}
// 	return o;
// }

/* Map loading ============================================================== */
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
/* ========================================================================== */

/* Map rendering ============================================================ */
void Map::renderMap(Mlx &mlx) {
	mlx.createImage();
	for (int i = 0; i < 100; i++)
		mlx.drawPixel(0 + i, 0, 0x00FF0000);
	mlx.putImage();
	mlx.destroyImage();
	return ;
}
/* ========================================================================== */
