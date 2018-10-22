//
// Created by aloha on 18.10.18.
//

#include "../include/wolf3d.h"

void rotate_r(t_main *m) {
    double oldDirX = m->cast.start_val.dir_x;
    m->cast.start_val.dir_x = m->cast.start_val.dir_x * cos(RAD_R) - m->cast.start_val.dir_y * sin(RAD_R);
    m->cast.start_val.dir_y = oldDirX * sin(RAD_R) + m->cast.start_val.dir_y * cos(RAD_R);
    double oldPlaneX = m->cast.start_val.plane_x;
    m->cast.start_val.plane_x = m->cast.start_val.plane_x * cos(RAD_R) - m->cast.start_val.plane_y * sin(RAD_R);
    m->cast.start_val.plane_y = oldPlaneX * sin(RAD_R) + m->cast.start_val.plane_y * cos(RAD_R);
}

void rotate_l(t_main *m) {
    double oldDirX = m->cast.start_val.dir_x;
    m->cast.start_val.dir_x = m->cast.start_val.dir_x * cos(RAD_L) - m->cast.start_val.dir_y * sin(RAD_L);
    m->cast.start_val.dir_y = oldDirX * sin(RAD_L) + m->cast.start_val.dir_y * cos(RAD_L);
    double oldPlaneX = m->cast.start_val.plane_x;
    m->cast.start_val.plane_x = m->cast.start_val.plane_x * cos(RAD_L) - m->cast.start_val.plane_y * sin(RAD_L);
    m->cast.start_val.plane_y = oldPlaneX * sin(RAD_L) + m->cast.start_val.plane_y * cos(RAD_L);
}

void move(t_main *m, int keycode) {
    double moveSpeed = 0.5;
    if (keycode == 0) {
        double iter_x = m->cast.start_val.pos_x + m->cast.start_val.dir_x * moveSpeed;
        double iter_y = m->cast.start_val.pos_y + m->cast.start_val.dir_y * moveSpeed;
        if (m->cast.map[(int)iter_x][(int)m->cast.start_val.pos_y] == 0)
            m->cast.start_val.pos_x += m->cast.start_val.dir_x * moveSpeed;
        if (m->cast.map[(int)m->cast.start_val.pos_x][(int)iter_y] == 0)
            m->cast.start_val.pos_y += m->cast.start_val.dir_y * moveSpeed;
    }
    if (keycode == 1) {
        double iter_x = m->cast.start_val.pos_x - m->cast.start_val.dir_x * moveSpeed;
        double iter_y = m->cast.start_val.pos_y - m->cast.start_val.dir_y * moveSpeed;
        if (m->cast.map[(int)iter_x][(int)m->cast.start_val.pos_y] == 0)
            m->cast.start_val.pos_x -= m->cast.start_val.dir_x * moveSpeed;
        if (m->cast.map[(int)m->cast.start_val.pos_x][(int)iter_y] == 0)
            m->cast.start_val.pos_y -= m->cast.start_val.dir_y * moveSpeed;
    }
}

int			press_exit(t_main *m)
{
	m = NULL;
	exit(0);
}

int press_key(int keycode, t_main *m) {
	printf("%d\n", keycode);
    if (keycode == ESC)
        exit(0);
    if (keycode == W)
        move(m, 0);
    if (keycode == S)
        move(m, 1);
    if (keycode == ROT_R)
        rotate_r(m);
    if (keycode == ROT_L)
        rotate_l(m);
    ft_image(&m->cast, m, &m->cast.text);
    return 0;
}
