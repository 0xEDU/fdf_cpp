#ifndef MLX_HPP
#define MLX_HPP

extern "C" {
	#include <mlx.h>
	#include <stdlib.h>
}

#include <iostream>

#define WIDTH 1200
#define HEIGHT 800

class Mlx {
	private:
		void *ptr;
		void *window;
	
	public:
		Mlx();
		~Mlx();

		void loop(void);
};

#endif // !MLX_HPP
