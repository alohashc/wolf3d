//
// Created by aloha on 15.10.18.
//

#include "../include/wolf3d.h"

void ft_image(t_casting *c, t_main *m, t_textures *t) {
    m->img.img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
    m->img.data = mlx_get_data_addr(m->img.img, &m->img.bpp, &m->img.size_l, &m->img.endian);
    raycasting(m, c, t);
    mlx_put_image_to_window(m->mlx, m->win, m->img.img, 0, 0);
    mlx_destroy_image(m->mlx, m->img.img);
}

void validateMapSize(t_casting *c, char **line) {
    char **size_line;

        size_line = ft_strsplit(*line, ' ');
        int iter = 0;
        while (size_line[iter]) {
            int i = 0;
            while (size_line[iter][i]) {
                if (size_line[iter][i] < '0' || size_line[iter][i] > '9')
                {
                    ft_putstr("Error: invalid values");
                    exit(0);
                }
                i++;
            }
            iter++;
        }
        if (iter != 2)
        {
            ft_putstr("Error: must be 2 arguments for map size");
            exit(0);
        }
        c->map_height = ft_atoi(size_line[0]);
        c->map_width = ft_atoi(size_line[1]);
        c->map = (int**)malloc(sizeof(int*) * c->map_height + 1);
}

void validateMap(t_casting *c, char *line, int cnt) {
    if ((ft_strlen(line) != c->map_width) || !line)
    {
        ft_putstr("Error: invalid map");
        exit(0);
    }

    c->map[cnt - 1] = (int*)malloc(sizeof(int) * c->map_width + 1);
    int i = 0;
    while (line[i]) {
        if (line[i] < '0' || line[i] > '9')
        {
            ft_putstr("Error: invalid map");
            exit(0);
        }
        c->map[cnt - 1][i] = line[i] - '0';
        i++;
    }
}

void readMap(t_casting *c, int ac, char **av) {
    int fd;
    char *line;
    int cnt = 0;

    fd = open(av[ac-1], O_RDONLY);
    if (fd == -1)
    {
        ft_putstr("Error: read from file");
        exit(0);
    }
    while (get_next_line(fd, &line) > 0) {
        if (cnt == 0)
           validateMapSize(c, &line);
        else
            validateMap(c, line, cnt);
        cnt++;
		free(line);
    }
    close(fd);
}

void init(t_main *m, t_casting *c, t_textures *t) {
    c->start_val.dir_x = -1;
    c->start_val.dir_y = 0;
    c->start_val.pos_x = 11;
    c->start_val.pos_y = 12;
    c->start_val.plane_x = 0;
    c->start_val.plane_y = 0.66;

    m->mlx = mlx_init();
    m->win = mlx_new_window(m->mlx, WIDTH, HEIGHT, "wolf3d");
    readMap(c, c->start_val.ac, c->start_val.av);
    textures(m, c, t);
}

