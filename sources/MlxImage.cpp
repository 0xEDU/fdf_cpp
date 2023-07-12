#include "MlxImage.hpp"

/* Default builders ======================================================== */
MlxImage::MlxImage()
	: _ptr(nullptr),
	_addr(nullptr),
	_bpp(0), _lineLength(0), _endian(0),
	_limits {0, 0, 0, 0}
{
	return ;
}

MlxImage::MlxImage(int width, int height)
	: _width(width), _height(height),
	_limits {this->_height / 2, -(this->_height / 2), -(this->_width / 2), this->_width / 2} {

}

MlxImage::~MlxImage() {
	return ;
}
/* ========================================================================= */

/* Accessors ================================================================ */
void *MlxImage::getPtr(void) const {
	return this->_ptr;
}
/* ========================================================================= */

/* Image builders ========================================================== */
void MlxImage::createImage(Mlx &mlx) {
	this->_ptr = mlx_new_image(mlx.getPtr(), this->_width, this->_height);
	this->_addr = mlx_get_data_addr(
		this->_ptr, &this->_bpp, &this->_lineLength, &this->_endian
	);
	return ;
}

void MlxImage::destroyImage(Mlx &mlx) {
	mlx_destroy_image(mlx.getPtr(), this->_ptr);
	return ;
}
/* ========================================================================= */

/* Pixel drawing =========================================================== */
static inline
bool validateLimits(int x, int y, int limits[4]) {
	if (x > limits[right]
		|| x < limits[left]
		|| y < limits[bottom]
		|| y > limits[top])
		return false;
	return true;
}

void MlxImage::writePixel(int x, int y, int color) {
	if (!validateLimits(x, y, this->_limits))
		return ;

	int		y_map = (this->_limits[top] - y) * this->_lineLength;
	int		x_map = (this->_limits[right] + x) * (this->_bpp / 8);
	char	*dst = this->_addr + y_map + x_map;
	int		*pixel = (int *)dst;
	*pixel = color;
	return ;
}
/* ========================================================================= */
