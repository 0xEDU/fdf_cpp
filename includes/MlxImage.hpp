#pragma once
#ifndef MLXIMAGE_HPP
#define MLXIMAGE_HPP

#include "Mlx.hpp"

enum Limits {
	top,
	bottom,
	left,
	right,
};

class Mlx;

class MlxImage {
	private:
		int	_width = 800;
		int	_height = 600;

		void	*_ptr;
		char	*_addr;
		int		_bpp;
		int		_lineLength;
		int		_endian;
		int		_limits[4];

	public:
		MlxImage();
		MlxImage(int width, int height);
		~MlxImage();

		void writePixel(int x, int y, int color);

		void createImage(Mlx &);
		void destroyImage(Mlx &);

		void *getPtr(void) const;
};

#endif
