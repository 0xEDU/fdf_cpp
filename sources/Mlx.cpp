#include "Mlx.hpp"
#include <cmath>
#include <mlx.h>

/* Default builders ======================================================== */
Mlx::Mlx() : _ptr(nullptr), _window(nullptr), _img(nullptr){
	return ;
}

Mlx::Mlx(int width, int height, const char *windowName)
	: _width(width), _height(height) {
	this->_ptr = mlx_init();
	this->_window =
		mlx_new_window(this->_ptr, width, height, (char *)windowName);
	return ;
}

Mlx::~Mlx() {
	free(this->_window);
	free(this->_ptr);
	return ;
}
/* ========================================================================== */

/* Accessors ================================================================ */
void *Mlx::getPtr(void) const {
	return this->_ptr;
}
/* ========================================================================== */

/* Window looping handling ================================================== */
static inline
int handleKeyPressEvents(int keyCode, Mlx &mlx) {
	if (keyCode == 65307)
		mlx.quit();
	return (0);
}

static inline
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

/* Image handling =========================================================== */
void Mlx::createImage() {
	this->_img = new MlxImage(this->_width, this->_height);
	this->_img->createImage(*this);
	return ;
}

void Mlx::putImage(void) {
	mlx_put_image_to_window(
		this->_ptr, this->_window, this->_img->getPtr(), 0, 0
	);
	return ;
}

void Mlx::destroyImage() {
	if (this->_img != nullptr) {
		this->_img->destroyImage(*this);
		delete this->_img;
	}
	return ;
}
/* ========================================================================== */

/* Drawing ================================================================== */
void Mlx::drawPixel(int x, int y, int color) {
	if (this->_img == nullptr)
		return ;
	this->_img->writePixel(x, y, color);
	return ;
}

void Mlx::drawLine(vector2 start, vector2 end, int color) {
	vector2 delta {
		.x = std::abs(end.x - start.x),
		.y = -std::abs(end.y - start.y)
	};
	vector2 s {
		.x = start.x < end.x ? 1 : -1,
		.y = start.y < end.y ? 1 : -1
	};
	int error = delta.x + delta.y;

	while (true) {
		this->drawPixel(start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		if ((2 * error) >= delta.y) {
			if (start.x == end.x)
				break ;
			error += delta.y;
			start.x += s.x;
		}
		if ((2 * error) <= delta.x) {
			if (start.y == end.y)
				break ;
			error += delta.x;
			start.y += s.y;
		}
	}
	return ;
}
/* ========================================================================== */
