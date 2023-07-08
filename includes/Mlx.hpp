#ifndef MLX_HPP
#define MLX_HPP

extern "C" {
	#include <mlx.h>
}

#include <iostream>
#include <cstdlib>

#define WIDTH 1200
#define HEIGHT 800

class Mlx {
	private:
		void *_ptr;
		void *_window;
	
	public:
		Mlx();
		~Mlx();

		void loop(void);
		void quit(void);
};

#endif // !MLX_HPP
