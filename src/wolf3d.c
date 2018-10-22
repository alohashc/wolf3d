//
// Created by aloha on 15.10.18.
//

#include "../include/wolf3d.h"

int main(int ac, char **av) {

    t_main m;
    t_casting c;
    t_textures t;

    c.start_val.ac = ac;
    c.start_val.av = av;
    init(&m, &c, &t);
    c.text = t;
    ft_image(&c, &m, &t);
    m.cast = c;
    mlx_hook(m.win, 2, 3, press_key, &m);
    mlx_loop(m.mlx);
    return 0;
}


// gcc wolf3d.c init.c raycasting.c events.c draw.c textures.c -lm -lmlx -lXext -lX11 -lft -L libft/ -L minilibx/  -I minilibx/ -I libft/

// TODO

// put t_main to t_casting
// add to events closing window and project "X";
