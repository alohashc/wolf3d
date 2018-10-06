#include <stdio.h>
#include <math.h>
#include "wold3d.h"

t_main m;

t_vector subVector(t_vector first, t_vector second) {
    t_vector result;

    result.x = first.x - second.x;
    result.y = first.y - second.y;

    return result;
}


t_vector addVector(t_vector first, t_vector second) {
    t_vector result;

    result.x = first.x + second.x;
    result.y = first.y + second.y;

    return result;
}

t_vector mulOnValue(t_vector vec, double val) {
    t_vector result;

    result.x = vec.x * val;
    result.y = vec.y * val;

    return result;
}



void ft_color(t_main *m, int x, int y, int color) {
    *((int*)(m->data + x * m->bpp / 8 + y * m->size_l)) = color;
}

void draw_line(t_main *m, int x, int start, int end, int color){
    while (start < end) {
        ft_color(m, x, start, color);
        start++;
    }
}

void draw(t_main *m, t_casting *c, int x, int drawStart, int drawEnd) {
    int color;

    switch(worldMap[c->mapX][c->mapY])
    {
        case 1:  color = 16711680;  break;
        case 2:  color = 65280;  break; //green
        case 3:  color = 255;   break; //blue
        case 4:  color = 16777215;  break; //white
        default: color = 16776960; break; //yellow
    }
    if (c->side == 1) {
        color = color / 2;
    }
    draw_line(m, x, drawStart, drawEnd, color);
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
        if (worldMap[c->mapX][c->mapY] > 0)
            c->hit = 1;
    }
}

void side(t_casting *c) {
    if (c->rayDir.x < 0) {
        c->stepX = -1;
        c->sideDistX = (c->pos.x - c->mapX) * c->deltaDistX;
    }
    else {
        c->stepX = 1;
        c->sideDistX = (c->mapX + 1.0 - c->pos.x) * c->deltaDistX;
    }
    if (c->rayDir.y < 0) {
        c->stepY = -1;
        c->sideDistY = (c->pos.y - c->mapY) * c->deltaDistY;
    }
    else {
        c->stepY = 1;
        c->sideDistY = (c->mapY + 1.0 - c->pos.y) * c->deltaDistY;
    }
}

void intersection(t_casting *c) {
    c->mapX = (int)c->pos.x;
    c->mapY = (int)c->pos.y;

    c->deltaDistX = fabs(1 / c->rayDir.x);
    c->deltaDistY = fabs(1 / c->rayDir.y);

    c->hit = 0;
}

void raycasting(t_main *m, t_casting *c){
    for (int x = 0; x < WIDTH; ++x) {
        double camX = 2 * x / (double)WIDTH - 1;
        c->rayDir = addVector(c->dir, mulOnValue(c->plane, camX));
        intersection(c);
        side(c);
        dda(c);
        if (c->side == 0) {
            c->lenWallDist = (c->mapX - c->pos.x + (double)(1 - c->stepX) / 2) / c->rayDir.x;
        }
        else
            c->lenWallDist = (c->mapY - c->pos.y + (double)(1 - c->stepY) / 2) / c->rayDir.y;
        int lineH = (int)(HEIGHT / c->lenWallDist);
        int start = -lineH / 2 + HEIGHT / 2;
        if (start < 0)
            start = 0;
        int end = lineH / 2 + HEIGHT / 2;
        if (end >= HEIGHT)
            end = HEIGHT - 1;
        draw(m, c, x, start, end);
    }
}

void ft_image(t_casting *c, t_main *m) {
    m->img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
    m->data = mlx_get_data_addr(m->img, &m->bpp, &m->size_l, &m->endian);
    raycasting(m, c);
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    mlx_destroy_image(m->mlx, m->img);
}

void rotate_r(t_casting *c) {
    double rad;

    rad = -M_PI * 2 / 180;
    double oldDirX = c->dir.x;
    c->dir.x = c->dir.x * cos(rad) - c->dir.y * sin(rad);
    c->dir.y = oldDirX * sin(rad) + c->dir.y * cos(rad);
    double oldPlaneX = c->plane.x;
    c->plane.x = c->plane.x * cos(rad) - c->plane.y * sin(rad);
    c->plane.y = oldPlaneX * sin(rad) + c->plane.y * cos(rad);
}

void rotate_l(t_casting *c) {
    double rad;

    rad = M_PI * 2 / 180;
    double oldDirX = c->dir.x;
    c->dir.x = c->dir.x * cos(rad) - c->dir.y * sin(rad);
    c->dir.y = oldDirX * sin(rad) + c->dir.y * cos(-rad);
    double oldPlaneX = c->plane.x;
    c->plane.x = c->plane.x * cos(rad) - c->plane.y * sin(rad);
    c->plane.y = oldPlaneX * sin(rad) + c->plane.y * cos(rad);
}

void move(t_casting *c, int keycode) {
    double moveSpeed = 1;
    if (keycode == 0) {
        t_vector x = addVector(c->pos, mulOnValue(c->dir, moveSpeed));
        if (worldMap[(int)x.x][(int)c->pos.y] == 0)
            c->pos.x += c->dir.x * moveSpeed;
        if (worldMap[(int)c->pos.x][(int)x.y] == 0)
            c->pos.y += c->dir.y * moveSpeed;
    }
    if (keycode == 1) {
        t_vector x = subVector(c->pos, mulOnValue(c->dir, moveSpeed));
        if (worldMap[(int)x.x][(int)c->pos.y] == 0)
            c->pos.x -= c->dir.x * moveSpeed;
        if (worldMap[(int)c->pos.x][(int)x.y] == 0)
            c->pos.y -= c->dir.y * moveSpeed;
    }
}

int press_key(int keycode, t_casting *c) {
    if (keycode == 53)
        exit(0);
    if (keycode == 126)
        move(c, 0);
    if (keycode == 125)
        move(c, 1);
    if (keycode == 2)
        rotate_r(c);
    if (keycode == 0)
        rotate_l(c);
    ft_image(c, &m);
    return 0;
}

void readMap(t_casting *c, int ac, char **av) {
    int fd;
    char *line;
    int cnt = 0;

    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        exit (0);
    while (get_next_line(fd, &line) > 0) {
        cnt++;
    }
}

int main(int ac, char **av) {
    t_casting c;

    readMap(&c, ac, av);
    c.dir.x = -1;
    c.dir.y = 0;
    c.pos.x = 11;
    c.pos.y = 12;
    c.plane.x = 0;
    c.plane.y = 0.66;

    //------------------------------------
    m.mlx = mlx_init();
    m.win = mlx_new_window(m.mlx, WIDTH, HEIGHT, "wolf3d");
    ft_image(&c, &m);
    mlx_hook(m.win, 2, 3, press_key, &c);
    mlx_loop(m.mlx);
    return 0;
}