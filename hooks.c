
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

int handle_key(int keycode, t_cub *cub)
{
    if (keycode == 65307)
    {
        mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
        exit(0);
    }
    else if (keycode == 119)
    {
        cub->player->player_x -= cos(cub->player->player_direction) * 0.1;
        cub->player->player_y += sin(cub->player->player_direction) * 0.1;
    }
    else if (keycode == 115)
    {
        cub->player->player_x += cos(cub->player->player_direction) * 0.1;
        cub->player->player_y -= sin(cub->player->player_direction) * 0.1;
    }
    else if (keycode == 97) // A
    {
        cub->player->player_x += cos(cub->player->player_direction - M_PI_2) * 0.1;
        cub->player->player_y -= sin(cub->player->player_direction - M_PI_2) * 0.1;
    }
    else if (keycode == 100) // D
    {
        cub->player->player_x += cos(cub->player->player_direction + M_PI_2) * 0.1;
        cub->player->player_y -= sin(cub->player->player_direction + M_PI_2) * 0.1;
    }
    else if (keycode == 65361) // ←
        cub->player->player_direction -= 0.1;
    else if (keycode == 65363) // →
        cub->player->player_direction += 0.1;

    // ⚡ redessine après chaque action
    draw_frame(cub);
    mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);

    return (0);
}

// int on_keydown(int key, t_cub *cub)
// {
//     if (key == K_ESC)
//         exit(0);
//     if (key == K_W)     cub->keys.w = 1;
//     if (key == K_A)     cub->keys.a = 1;
//     if (key == K_S)     cub->keys.s = 1;
//     if (key == K_D)     cub->keys.d = 1;
//     if (key == K_LEFT)  cub->keys.left = 1;
//     if (key == K_RIGHT) cub->keys.right = 1;
//     return (0);
// }

// int on_keyup(int key, t_cub *cub)
// {
//     if (key == K_W)     cub->keys.w = 0;
//     if (key == K_A)     cub->keys.a = 0;
//     if (key == K_S)     cub->keys.s = 0;
//     if (key == K_D)     cub->keys.d = 0;
//     if (key == K_LEFT)  cub->keys.left = 0;
//     if (key == K_RIGHT) cub->keys.right = 0;
//     return (0);
// }
int hooks_game(t_cub *cub)
{
    mlx_hook(cub->mlx.win, 2, 1L<<0, handle_key, cub);;
    // mlx_hook(cub->mlx.win, 2, 0, on_keydown, cub);
    return (0);
}
