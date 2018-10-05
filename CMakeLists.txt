cmake_minimum_required(VERSION 3.12)
project(wolf3d C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-lmlx -lXext -lX11 -L minilibx/ -I minilibx/)

add_executable(wolf3d main.c wold3d.h)

