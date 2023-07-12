#include "fdf.hpp"

int main(int argc, char *argv[]) {
	(void)argv;
	if (argc != 2) {
		std::cerr << "Usage: ./fdf [MAP]" << std::endl;
		return (1);
	}

	Mlx mlx(WIDTH, HEIGHT, "fdf");
	Map map;

	map.loadMap(argv[1]);
	map.renderMap(mlx);
	mlx.loop();
	return (0);
}
