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



static double cast_ray(t_cub *cub, double ray_angle, int *out_side)
{
    double posX = cub->player->player_x + 0.5;
    double posY = cub->player->player_y + 0.5;

    double rayDirX = cos(ray_angle);
    double rayDirY = sin(ray_angle);

    int mapX;
    mapX = (int)posX;
    int mapY;
    mapY = (int)posY;

    double deltaDistX = (rayDirX == 0.0) ? 1e30 : fabs(1.0 / rayDirX);
    double deltaDistY = (rayDirY == 0.0) ? 1e30 : fabs(1.0 / rayDirY);

    int stepX, stepY;
    double sideDistX, sideDistY;

    if (rayDirX < 0) { stepX = -1; sideDistX = (posX - mapX) * deltaDistX; }
    else             { stepX =  1; sideDistX = (mapX + 1.0 - posX) * deltaDistX; }
    if (rayDirY < 0) { stepY = -1; sideDistY = (posY - mapY) * deltaDistY; }
    else             { stepY =  1; sideDistY = (mapY + 1.0 - posY) * deltaDistY; }

    int hit;
    int side;
    hit = 0;
    side = 0;
    int safety;
    safety = cub->width * cub->height * 4;
    while (!hit && safety-- > 0)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0; // mur vertical
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1; // mur horizontal
        }
        if (is_wall_or_void(cub, mapX, mapY))
            hit = 1;
    }

    double perp;
    if (side == 0)
        perp = (mapX - posX + (1 - stepX) / 2.0) / (rayDirX == 0.0 ? 1e-9 : rayDirX);
    else
        perp = (mapY - posY + (1 - stepY) / 2.0) / (rayDirY == 0.0 ? 1e-9 : rayDirY);

    if (out_side) *out_side = side;
    if (perp < 1e-6) perp = 1e-6;
    return fabs(perp);
}

void draw_walls(t_cub *cub)
{
    int screen_w;
    int x;

    x = 0;
    screen_w= cub->width * TILE_SIZE;
    while (x < screen_w)
    {
        double cam = ((double)x / (double)screen_w) - 0.5;
        double ray_angle = cub->player->player_direction + cam * FOV_RAD;

        int side;
        side = 0;
        double dist = cast_ray(cub, ray_angle, &side);

        int line_h;
        line_h = (int)((cub->height * TILE_SIZE) / dist);
        int draw_s;
        draw_s = -line_h / 2 + (cub->height * TILE_SIZE) / 2;
        int draw_e;
        draw_e = line_h / 2 + (cub->height * TILE_SIZE) / 2;

        int wall_color;
        wall_color = (side == 0) ? 0xBBBBBB : 0x999999; // léger shading
        draw_vertical_line(cub, x, draw_s, draw_e, wall_color);
        x++;
    }
}


void draw_frame(t_cub *cub)
{
    int y;
    int color;
    int x;

    y = 0;
    while (y < cub->height * TILE_SIZE)
    {
        if (y < cub->height * TILE_SIZE / 2)
            color = get_color(cub->ceiling_colors);
        else
            color = get_color(cub->ground_colors);

        x = 0;
        while (x < cub->width * TILE_SIZE)
        {
            put_pixel(cub, x, y, color);
            x++;
        }
        y++;
    }
    draw_walls(cub);
}
