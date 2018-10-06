//
// Created by aloha on 27.09.18.
//

#ifndef WOLF3D_WOLD3D_H
#define WOLF3D_WOLD3D_H

#include "minilibx/mlx.h"
#include <stdlib.h>
#include "libft/libft.h"

#define mapWidth 24
#define mapHeight 24
#define WIDTH 512
#define HEIGHT 384

int worldMap[mapWidth][mapHeight]=
        {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };

typedef struct s_main{
    void    *mlx;
    void    *win;
    void    *img;
    char    *data;
    int     bpp;
    int     size_l;
    int     endian;
} t_main;

typedef struct s_vector {
    double x;
    double y;
} t_vector;

typedef struct {
    t_vector dir;
    t_vector pos;
    t_vector plane;
    t_vector rayDir;
    int         stepX;
    int         stepY;
    int         mapX;
    int         mapY;
    int         hit;
    int         side;
    double      lenWallDist;
    double      sideDistX;
    double      sideDistY;
    double      deltaDistX;
    double      deltaDistY;
    int         **map;
} t_casting;

#endif //WOLF3D_WOLD3D_H
