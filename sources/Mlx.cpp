#include "Mlx.hpp"

Mlx::Mlx() {
	char windowName[] = "fdf";
	this->_ptr = mlx_init();
	this->_window = mlx_new_window(this->_ptr, WIDTH, HEIGHT, windowName);
	return ;
}

Mlx::~Mlx() {
	free(this->_window);
	free(this->_ptr);
	return ;
}

static inline
int handleKeyPressEvents(int keyCode, Mlx &mlx) {
	if (keyCode == 65307)
		mlx.quit();
	return (0);
}

void Mlx::loop(void) {
	int (*hkpe)() = reinterpret_cast<int (*)()>(handleKeyPressEvents);

	mlx_key_hook(this->_window, hkpe, this);
	mlx_loop(this->_ptr);
	return ;
}

void Mlx::quit(void) {
	mlx_destroy_window(this->_ptr, this->_window);
	mlx_destroy_display(this->_ptr);
	if (this->_ptr)
		free(this->_ptr);
	std::exit(0);
}
