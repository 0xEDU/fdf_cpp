#pragma once
#ifndef MLX_HPP
#define MLX_HPP

extern "C" {
	#include <mlx.h>
}

#include <iostream>
#include <cstdlib>

#include "MlxImage.hpp"

#define WIDTH 1200
#define HEIGHT 800

class MlxImage;

class Mlx {
	private:
		void *_ptr;
		void *_window;
		MlxImage *_img;
	
	public:
		Mlx();
		~Mlx();

		void loop(void);
		void quit(void);

		void createImage(void);
		void putImage(void);
		void destroyImage(void);
	
		void drawPixel(int x, int y, int color);

		void *getPtr(void) const;
};

#endif // !MLX_HPP
