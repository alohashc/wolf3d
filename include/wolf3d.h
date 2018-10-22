//
// Created by aloha on 15.10.18.
//

#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H

#include "../minilibx/mlx.h"
#include <stdlib.h>
#include <math.h>
#include "../libft/libft.h"

#define WIDTH 640
#define HEIGHT 480

#define t_Width 64
#define t_Height 64
#define RAD_R -M_PI * 2 / 180
#define RAD_L M_PI * 2 / 180

#define W 126
#define S 125
#define ROT_R 124
#define ROT_L 123
#define ESC 53


typedef struct s_img {
    void *img;
    int bpp;
    int size_l;
    int endian;
    int w;
    int h;
    char *data;
} t_img;

typedef struct s_draw {
    int         drawStart;
    int         drawEnd;
    int         tex_pixel;
    int         img_pixel;
}t_draw;

typedef struct s_textures {
    int         texture_x;
    int         tex_type;
    double      wall_x;
    double      startTexFloor_x;
    double      startTexFloor_y;
    double      d_wall;
    double      d_player;
    double      d_current;
} t_textures;

typedef struct s_start{
    int ac;
    char **av;
    double dir_x;
    double dir_y;
    double pos_x;
    double pos_y;
    double plane_x;
    double plane_y;
}t_start;



typedef struct s_casting{
    double rayDir_x;
    double rayDir_y;
    int         stepX;
    int         stepY;
    int         mapX;
    int         mapY;
    int         hit;
    int         side;
    int         **map;
    int         map_width;
    int         map_height;
    double      d_perpWall;
    int         lineH;
    double      sideDistX;
    double      sideDistY;
    double      deltaDistX;
    double      deltaDistY;
    t_textures  text;
    t_img       img[6];
    t_start     start_val;
    t_draw      drw;
} t_casting;

typedef struct s_main{
    void    *mlx;
    void    *win;
    t_img   img;
    t_casting  cast;
}t_main;


void init(t_main *m, t_casting *c, t_textures *t);
void ft_image(t_casting *c, t_main *m, t_textures *t);
void readMap(t_casting *c, int ac, char **av);
void textures(t_main *m, t_casting *c, t_textures *t);
void draw(t_main *m, t_casting *c, t_textures *t, int x);
void ft_color(t_main *m, t_casting *c, int num, int side);
void raycasting(t_main *m, t_casting *c, t_textures *t);
int press_key(int keycode, t_main *m);
int	press_exit(t_main *m);

#endif //WOLF3D_WOLF3D_H
