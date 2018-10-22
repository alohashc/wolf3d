NAME = wolf3d

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC_FILES = $(shell ls $(SRC_DIR))

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC =	-I include/ \
		-I ./libft

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

GCC = gcc

all: $(NAME)

$(NAME): $(OBJ) ./libft/libft.a
	$(GCC) $(OBJ) -L./libft/ -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)

./libft/libft.a:
	make -C libft

$(OBJ_DIR)%.o : $(SRC_DIR)%.c include/wolf3d.h
	$(GCC) $(INC) -c $< -o $@

clean:
	make clean -C libft
	rm -rf $(OBJ)

fclean: clean
	rm -rf libft/libft.a
	rm -rf $(NAME)

re: fclean all
