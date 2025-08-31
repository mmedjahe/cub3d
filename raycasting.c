/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:06:16 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/08/20 22:32:31 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// double raycast(t_cub *cub, double angle)
// {
//     double rayx;
//     double rayy;

//     rayx = cub->player->player_x;
//     rayy = cub->player->player_y;
// }


// Remplace ta draw_frame par une version pixel-based
void draw_frame(t_cub *cub)
{
    int screen_w = cub->width * TILE_SIZE;
    int screen_h = cub->height * TILE_SIZE;

    int ceil_color = cub->ceiling_colors[0] * 65536
                   + cub->ceiling_colors[1] * 256
                   + cub->ceiling_colors[2];

    int floor_color = cub->ground_colors[0] * 65536
                    + cub->ground_colors[1] * 256
                    + cub->ground_colors[2];

    int y = 0;
    while (y < screen_h)
    {
        int color;
        if (y < screen_h / 2)
            color = ceil_color;
        else
            color = floor_color;

        int x = 0;
        while (x < screen_w)
        {
            put_pixel(cub, x, y, color);
            x++;
        }
        y++;
    }
}




// void draw_frame(t_cub *cub)
// {

//     int scr_w;
//     int scr_y;

//     scr_w = cub->width * 32;
//     scr_y = cub->height * 32;

//     y = 0;
//     while (cub->map[y])
//     {
//         x = 0;
//         while (cub->map[y][x])
//         {
//             if (cub->map[y][x] == '1')
//                 draw_tile(cub, x, y, 0x8B4513);
//             else if (cub->map[y][x] == '0')
//                 draw_tile(cub, x, y, 0xD3D3D3);
//             else if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
//                   || cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
//                 draw_tile(cub, x, y, 0xFFFFFF);
//             x++;
//         }
//         y++;
//     }
// }
