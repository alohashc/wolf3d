//
// Created by aloha on 18.10.18.
//

#include "../include/wolf3d.h"

void ft_color(t_main *m, t_casting *c, int num, int side) {
    m->img.data[c->drw.img_pixel] = c->img[num].data[c->drw.tex_pixel];
    m->img.data[c->drw.img_pixel + 1] = c->img[num].data[c->drw.tex_pixel + 1];
    m->img.data[c->drw.img_pixel + 2] = c->img[num].data[c->drw.tex_pixel + 2];
}

void draw(t_main *m, t_casting *c, t_textures *t, int x) {
    int y = c->drw.drawStart;

    while (y++ < c->drw.drawEnd)
    {
        int d = y * 256 - HEIGHT * 128 + c->lineH * 128;
        int texY = ((d * t_Height) / c->lineH) / 256;
        c->drw.tex_pixel = c->img[t->tex_type].bpp / 8 * t->texture_x + texY * c->img[t->tex_type].size_l;
        c->drw.img_pixel = x * m->img.bpp / 8 + y * m->img.size_l;
        ft_color(m, c, t->tex_type, c->side);
    }
}
