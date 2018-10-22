//
// Created by aloha on 15.10.18.
//

#include "../include/wolf3d.h"
#include <stdio.h>

void texturesFloorAndCeiling(t_main *m, t_casting *c, t_textures *t) {
    c->img[4].img = mlx_xpm_file_to_image(m->mlx, "XPM/floor.XPM", &c->img[4].w, &c->img[4].h);
    c->img[4].data = mlx_get_data_addr(c->img[4].img, &c->img[4].bpp, &c->img[4].size_l, &c->img[4].endian);
    c->img[5].img = mlx_xpm_file_to_image(m->mlx, "XPM/ceiling.XPM", &c->img[5].w, &c->img[5].h);
    c->img[5].data = mlx_get_data_addr(c->img[5].img, &c->img[4].bpp, &c->img[5].size_l, &c->img[5].endian);
}

void texturesWall(t_main *m, t_casting *c, t_textures *t) {
    c->img[0].img = mlx_xpm_file_to_image(m->mlx, "XPM/wood.XPM", &c->img[0].w, &c->img[0].h);
    c->img[0].data = mlx_get_data_addr(c->img[0].img, &c->img[0].bpp, &c->img[0].size_l, &c->img[0].endian);
    c->img[1].img = mlx_xpm_file_to_image(m->mlx, "XPM/bluestone.XPM", &c->img[1].w, &c->img[1].h);
    c->img[1].data = mlx_get_data_addr(c->img[1].img, &c->img[1].bpp, &c->img[1].size_l, &c->img[1].endian);
    c->img[2].img = mlx_xpm_file_to_image(m->mlx, "XPM/greystone.XPM", &c->img[2].w, &c->img[2].h);
    c->img[2].data = mlx_get_data_addr(c->img[2].img, &c->img[2].bpp, &c->img[2].size_l, &c->img[2].endian);
    c->img[3].img = mlx_xpm_file_to_image(m->mlx, "XPM/redbrick.XPM", &c->img[3].w, &c->img[3].h);
    c->img[3].data = mlx_get_data_addr(c->img[3].img, &c->img[3].bpp, &c->img[3].size_l, &c->img[3].endian);
}

void textures(t_main *m, t_casting *c, t_textures *t) {
    texturesWall(m, c, t);
    texturesFloorAndCeiling(m, c, t);
}
