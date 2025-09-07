/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:06:16 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/07 22:28:54 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char letter_orientation(int side, double ray_dir_x, double ray_dir_y)
{
    char orientation;

    if (side == 0)
    {
        if (ray_dir_x > 0)
            orientation = 'e';
        else
            orientation = 'w';
    }
    else
    {
        if (ray_dir_y > 0)
            orientation = 's';
        else
            orientation = 'n';
    }
    return (orientation);
}

void	draw_walls(t_cub *cub)
{
	int		screen_w;
	int		x;
	double	cam;
	double	ray_angle;
		int side;
	double	dist;
	double	ray_dir_x;
	double	ray_dir_y;
	double	perp_dist;
		int line_h;
		double safe_dist;
	t_img	*tex;
		double wallX;
	int		texX;

	x = 0;
	screen_w = cub->width * TILE_SIZE;
	while (x < screen_w)
	{
		cam = ((double)x / (double)screen_w) - 0.5;
		ray_angle = cub->player->player_direction + cam * FOV_RAD;
		side = 0;
		dist = cast_ray(cub, ray_angle, &side);
		ray_dir_x = cos(ray_angle);
		ray_dir_y = sin(ray_angle);
		perp_dist = dist * cos(ray_angle - cub->player->player_direction);
		if (perp_dist > 1e-6)
			safe_dist = perp_dist;
		else
			safe_dist = 1e-6;
		line_h = (int)((cub->height * TILE_SIZE) / safe_dist);

		tex = pick_texture(cub, letter_orientation(side, ray_dir_x, ray_dir_y));
		if (side == 0)
			wallX = cub->player->player_y + perp_dist * ray_dir_y;
		else
			wallX = cub->player->player_x + perp_dist * ray_dir_x;
		wallX -= floor(wallX);
		texX = (int)(wallX * (double)tex->w);
		if (side == 0 && ray_dir_x > 0)
			texX = tex->w - texX - 1;
		if (side == 1 && ray_dir_y < 0)
			texX = tex->w - texX - 1;
		draw_vertical_line(cub, x, line_h, texX);
		x++;
	}
}

void	draw_frame(t_cub *cub)
{
	int	y;
	int	color;
	int	x;

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
