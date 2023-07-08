#include "Mlx.hpp"

Mlx::Mlx() {
	char windowName[] = "fdf";
	this->ptr = mlx_init();
	this->window = mlx_new_window(this->ptr, WIDTH, HEIGHT, windowName);
	return ;
}

Mlx::~Mlx() {
	free(this->window);
	free(this->ptr);
	return ;
}

void Mlx::loop(void) {
	mlx_loop(this->ptr);
	return ;
}
