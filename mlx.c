/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 00:36:40 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/08/04 01:15:23 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_tile(t_cub *cub, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            put_pixel(cub, x * TILE_SIZE + j, y * TILE_SIZE + i, color);
            j++;
        }
        i++;
    }
}

void draw_frame(t_cub *cub)
{
    int y;
    int x;

    y = 0;
    while (cub->map[y])
    {
        x = 0;
        while (cub->map[y][x])
        {
            if (cub->map[y][x] == '1')
                draw_tile(cub, x, y, 0x8B4513);
            else if (cub->map[y][x] == '0')
                draw_tile(cub, x, y, 0xD3D3D3); 
            else if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
                  || cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
                draw_tile(cub, x, y, 0xFFFFFF); 
            x++;
        }
        y++;
    }
}

void put_pixel(t_cub *cub, int x, int y, int color)
{
    char *dst;

    dst = cub->mlx.addr + (y * cub->mlx.line_length + x * (cub->mlx.bits_per_pixel / 8));
    *(unsigned int *) dst = color;
}