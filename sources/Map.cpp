#include "Map.hpp"

/* Default builders ========================================================= */
Map::Map() : _map(std::map<int, vector3>()), _rows(0), _cols(0) {
	return ;
}

Map::~Map() {
	return ;
}
/* ========================================================================== */

/* Accessors ================================================================ */
std::map<int, vector3> &Map::getMap(void) {
	return this->_map;
}
/* ========================================================================== */

std::ostream &operator<<(std::ostream &o, vector3 &v) {
	o << "x = " << v.x
		<< " | y = " << v.y
		<< " | z = " << v.z
		<< std::endl;
	return o;
}

std::ostream &operator<<(std::ostream &o, std::map<int, vector3> &map) {
	for (auto i : map) {
		o << "KEY = " << i.first << " | "
			<< i.second
			<< std::endl;
	}
	return o;
}

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
			this->_map.insert(std::make_pair(i, vector3 {x, y, z}));
			y++;
			i++;
		}
		x++;
	}
	this->_rows = x;
	this->_cols = y;
	return ;
}
/* ========================================================================== */

/* Map rendering ============================================================ */
void Map::writeMapToImage(Mlx &mlx) {
	for (auto it : this->_map) {
		int position = it.first;

		auto right = position + this->_cols;
		if (right < this->_rows * this->_cols) {
			vector3 next = this->_map[right];
			mlx.drawLine({it.second.x, it.second.y}, {next.x, next.y}, 0x00FFFFFF);
		}
		auto top = position % this->_cols == 0 ? position - this->_cols : position - 1;
		if (top >= 0) {
			vector3 next = this->_map[top];
			mlx.drawLine({it.second.x, it.second.y}, {next.x, next.y}, 0x00FFFFFF);
		}
	}
	return ;
}

static inline
void scaleMap(std::map<int, vector3> &map, int scaleValue) {
	for (auto it : map) {
		auto position = it.first;
		map[position].x *= scaleValue;
		map[position].y *= scaleValue;
		map[position].z *= scaleValue / 2;
	}
	return ;
}

void Map::transformMap(void (*transformation)(vector3 &)) {
	for(auto it : this->_map)
		transformation(this->_map[it.first]);
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
