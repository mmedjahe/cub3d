
#include "cub3d.h"

// # include <X11/keysym.h>
// # define K_ESC   65307
// # define K_W     119
// # define K_A     97
// # define K_S     115
// # define K_D     100
// # define K_LEFT  65361
// # define K_RIGHT 65363
// #endif

static void normalize_angle(double *a)
{
    double TWO_PI;

    TWO_PI = 2.0 * M_PI;
    while (*a < 0)
        *a += TWO_PI;
    while (*a >= TWO_PI)
        *a -= TWO_PI;
}

int handle_key(int keycode, t_cub *cub)
{
    const double ms = 0.1;
    const double rs = 0.1;
    double a = cub->player->player_direction;
    double dx = cos(a);
    double dy = sin(a);

    if (keycode == 65307) {
        mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
        exit(0);
    }
    else if (keycode == 119) {
        cub->player->player_x += dx * ms;
        cub->player->player_y += dy * ms;
    }
    else if (keycode == 115) {
        cub->player->player_x -= dx * ms;
        cub->player->player_y -= dy * ms;
    }
    else if (keycode == 100) {
        cub->player->player_x += (-sin(a)) * ms;
        cub->player->player_y += ( cos(a)) * ms;
    }
    else if (keycode == 97) {
        cub->player->player_x -= (-sin(a)) * ms;
        cub->player->player_y -= ( cos(a)) * ms;
    }
    else if (keycode == 65361) {
        cub->player->player_direction -= rs;
        normalize_angle(&cub->player->player_direction);
    }
    else if (keycode == 65363) {
        cub->player->player_direction += rs;
        normalize_angle(&cub->player->player_direction);
    }

    draw_frame(cub);
    mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
    return 0;
}
