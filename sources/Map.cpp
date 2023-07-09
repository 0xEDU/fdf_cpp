#include "Map.hpp"

/* Default builders ========================================================= */
Map::Map() : _map(std::map<int, vector3>()), _rows(0), _cols(0) {
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
	int						x = 0, y = 0, i = 0;

	while (std::getline(input, line)) {
		std::istringstream iss(line);
		int z;

		y = 0;
		while (iss >> z) {
			vector3 v {x, y ,z};

			this->_map.insert(std::make_pair(i, v));
			char whitespace;
			iss >> whitespace;
			y++;
		}
		i++;
		x++;
	}
	return ;
}
/* ========================================================================== */

/* Map rendering ============================================================ */
static inline
void scaleMap(std::map<int, vector3> &map, int scaleValue) {
	for (auto it : map) {
		it.second.x *= scaleValue;
		it.second.y *= scaleValue;
		it.second.z *= scaleValue / 2;
	}
	return ;
}

void Map::transformMap(void (*transformation)(vector3 &)) {
	for(auto it : this->_map)
		transformation(it.second);
	return ;
}

void Map::isometricRender(void) {
	int scaleValue =
		HEIGHT / std::sqrt(std::pow(this->_rows, 2) + std::pow(this->_cols, 2));
	scaleMap(this->_map, scaleValue);
	transformMap(&rotate);
	transformMap(&down);
	transformMap(&extrude);
	return ;
}

void Map::renderMap(Mlx &mlx) {
	mlx.createImage();
	this->isometricRender();
	this->writeMapToImage(mlx);
	mlx.putImage();
	mlx.destroyImage();
	return ;
}
/* ========================================================================== */
