NAME = fdf

PATH_SRCS = ./sources/
PATH_INCLUDES = ./includes/
PATH_OBJS = ./objects/

MLXFLAGS = -lmlx -lXext -lX11

SRCS =	main.cpp \
		Map.cpp \
		Mlx.cpp \
		MlxImage.cpp

OBJS = ${SRCS:%.cpp=${PATH_OBJS}%.o}

INCLUDES = -I$(PATH_INCLUDES)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@clang++ $(FLAGS) $(OBJS) $(MLXFLAGS) -o $(NAME)

$(PATH_OBJS)%.o: $(PATH_SRCS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@clang++ $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Object creation done!\033[0m"

clean:
	@rm -rf $(PATH_OBJS)
	@echo "\033[1;93m[SUCCESS] Objects removed!\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;93m[SUCCESS] Full clean done!\033[0m"

re: fclean all

.PHONY: all clean fclean re
