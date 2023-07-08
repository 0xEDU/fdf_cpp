#include "Mlx.hpp"

/* Default builders ======================================================== */
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
/* ========================================================================== */

/* Window looping handling ================================================== */
static inline
int handleKeyPressEvents(int keyCode, Mlx &mlx) {
	if (keyCode == 65307)
		mlx.quit();
	return (0);
}

int clickPressEvents(Mlx &mlx) {
	mlx.quit();
	return (0);
}

void Mlx::loop(void) {
	int (*hkpe)() = reinterpret_cast<int (*)()>(handleKeyPressEvents);
	int (*cpe)() = reinterpret_cast<int (*)()>(clickPressEvents);

	mlx_key_hook(this->_window, hkpe, this);
	mlx_hook(this->_window, 17, 0, cpe, this);
	mlx_loop(this->_ptr);
	return ;
}
/* ========================================================================== */

/* Window closing =========================================================== */
void Mlx::quit(void) {
	mlx_destroy_window(this->_ptr, this->_window);
	mlx_destroy_display(this->_ptr);
	if (this->_ptr)
		free(this->_ptr);
	std::exit(0);
}
/* ========================================================================== */
