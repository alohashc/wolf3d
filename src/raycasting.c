//
// Created by aloha on 18.10.18.
//

#include "../include/wolf3d.h"

void ft_floor(t_main *m, t_casting *c, t_textures *t, int x) {
    if(c->side == 0 && c->rayDir_x > 0)
    {
        t->startTexFloor_x = c->mapX;
        t->startTexFloor_y = c->mapY + t->wall_x;
    }
    else if(c->side == 0 && c->rayDir_x < 0)
    {
        t->startTexFloor_x = c->mapX + 1.0;
        t->startTexFloor_y = c->mapY + t->wall_x;
    }
    else if(c->side == 1 && c->rayDir_y > 0)
    {
        t->startTexFloor_x = c->mapX + t->wall_x;
        t->startTexFloor_y = c->mapY;
    }
    else
    {
        t->startTexFloor_x = c->mapX + t->wall_x;
        t->startTexFloor_y = c->mapY + 1.0;
    }
    t->d_wall = c->d_perpWall;
    t->d_player = 0.0;

    if (c->drw.drawEnd < 0) c->drw.drawEnd = HEIGHT;
    for(int y = c->drw.drawEnd + 1; y < HEIGHT; y++)
    {
        t->d_current = HEIGHT / (2.0 * y - HEIGHT);

        double weight = (t->d_current - t->d_player) / (t->d_wall - t->d_player);

        double currentFloorX = weight * t->startTexFloor_x + (1.0 - weight) * c->start_val.pos_x;
        double currentFloorY = weight * t->startTexFloor_y + (1.0 - weight) * c->start_val.pos_y;

        int floorTexX, floorTexY;
        floorTexX = (int)(currentFloorX * t_Width) % t_Width;
        floorTexY = (int)(currentFloorY * t_Height) % t_Height;
        c->drw.tex_pixel = c->img[4].bpp / 8 * floorTexX + floorTexY * c->img[4].size_l;
        c->drw.img_pixel = x * m->img.bpp / 8 + y * m->img.size_l;
        ft_color(m, c, 4, c->side);
        c->drw.img_pixel = x * m->img.bpp / 8 + (HEIGHT - y) * m->img.size_l;
        ft_color(m, c, 5, c->side);

    }
}

void texture(t_casting *c, t_textures *t) {
    t->tex_type = c->map[c->mapX][c->mapY] - 1;

    if (c->side == 0)
        t->wall_x = c->start_val.pos_y + c->d_perpWall * c->rayDir_y;
    else
        t->wall_x = c->start_val.pos_x + c->d_perpWall * c->rayDir_x;
    t->wall_x -= floor((t->wall_x));
    t->texture_x = (int)(t->wall_x * (double)t_Width);

    if(c->side == 0 && c->rayDir_x > 0)
        t->texture_x = t_Width - t->texture_x - 1;
    if(c->side == 1 && c->rayDir_y < 0)
        t->texture_x = t_Width - t->texture_x - 1;
}

void dda(t_casting *c) {
    while (c->hit == 0) {
        if (c->sideDistX < c->sideDistY) {
            c->sideDistX += c->deltaDistX;
            c->mapX += c->stepX;
            c->side = 0;
        }
        else {
            c->sideDistY += c->deltaDistY;
            c->mapY += c->stepY;
            c->side = 1;
        }
        if (c->map[c->mapX][c->mapY] > 0)
            c->hit = 1;
    }
}

void side(t_casting *c) {
    if (c->rayDir_x < 0) {
        c->stepX = -1;
        c->sideDistX = (c->start_val.pos_x - c->mapX) * c->deltaDistX;
    }
    else {
        c->stepX = 1;
        c->sideDistX = (c->mapX + 1.0 - c->start_val.pos_x) * c->deltaDistX;
    }
    if (c->rayDir_y < 0) {
        c->stepY = -1;
        c->sideDistY = (c->start_val.pos_y - c->mapY) * c->deltaDistY;
    }
    else {
        c->stepY = 1;
        c->sideDistY = (c->mapY + 1.0 - c->start_val.pos_y) * c->deltaDistY;
    }
}

void intersection(t_casting *c, int x) {
    double camX;

    camX = 2 * x / (double)WIDTH - 1;
    c->rayDir_x = c->start_val.dir_x + c->start_val.plane_x * camX;
    c->rayDir_y = c->start_val.dir_y + c->start_val.plane_y * camX;

    c->mapX = (int)c->start_val.pos_x;
    c->mapY = (int)c->start_val.pos_y;

    c->deltaDistX = fabs(1 / c->rayDir_x);
    c->deltaDistY = fabs(1 / c->rayDir_y);

    c->hit = 0;
}

void raycasting(t_main *m, t_casting *c, t_textures *t){
    int x = 0;

    while (x++ < WIDTH)
    {
        intersection(c, x);
        side(c);
        dda(c);
        if (c->side == 0)
            c->d_perpWall = (c->mapX - c->start_val.pos_x + (double)(1 - c->stepX) / 2) / c->rayDir_x;
        else
            c->d_perpWall = (c->mapY - c->start_val.pos_y + (double)(1 - c->stepY) / 2) / c->rayDir_y;
        c->lineH = (int)(HEIGHT / c->d_perpWall);
        c->drw.drawStart = -c->lineH / 2 + HEIGHT / 2;
        if (c->drw.drawStart < 0)
            c->drw.drawStart = 0;
        c->drw.drawEnd = c->lineH / 2 + HEIGHT / 2;
        if (c->drw.drawEnd >= HEIGHT)
            c->drw.drawEnd = HEIGHT - 1;
        texture(c, t);
        draw(m, c, t, x);
        ft_floor(m, c, t,x);
    }
}
