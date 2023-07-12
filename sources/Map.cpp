#include "Map.hpp"

/* Default builders ========================================================= */
Map::Map()
	: _map(std::map<int, vector3>()), _rows(0), _cols(0) {
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

/* Map loading ============================================================== */
void Map::loadMap(char *mapFile) {
	std::ifstream			input(mapFile);
	std::string				line;
	int						x = 0, y = 0, i = 0;

	while (std::getline(input, line)) {
		std::istringstream iss(line);
		std::string token;
		int z;
		int color;

		y = 0;
		while (std::getline(iss, token, ' ')) {
			try {
				std::size_t commaPos = token.find(',');
				bool hasComma = (commaPos != std::string::npos);

				std::string valueStr = token.substr(0, commaPos);
				std::string colorStr = token.substr(commaPos + 1);

				z = std::stoi(hasComma
					? valueStr
					: token
				);
				color = hasComma
					? std::stoi(colorStr, 0, 16)
					: 0x00FFFFFF;
			} catch (const std::invalid_argument &e) {
				continue ;
			}
			this->_map.insert(std::make_pair(i, vector3 {x, y, z, color}));
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
		vector3 point = it.second;

		int right = position + this->_cols;
		if (right < this->_rows * this->_cols) {
			vector3 next = this->_map[right];
			mlx.drawLine(
				{point.x, point.y},
				{next.x, next.y},
				point.color
			);
		}
		int top = position % this->_cols == 0
			? position - this->_cols
			: position - 1;
		if (top >= 0) {
			vector3 next = this->_map[top];
			mlx.drawLine(
				{point.x, point.y},
				{next.x, next.y},
				point.color
			);
		}
	}
	return ;
}

static inline
void mirrorMap(std::map<int, vector3> &map, int rows, int cols) {
	for (auto it: map) {
		auto position = it.first;
		
		map[position].x = rows - map[position].x;
		map[position].y = cols - map[position].y;
	}
	return;
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
		HEIGHT / std::sqrt(
			std::pow(this->_rows, 2) + std::pow(this->_cols, 2)
		);

	scaleMap(this->_map, scaleValue);
	mirrorMap(this->_map, this->_rows, this->_cols);
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
