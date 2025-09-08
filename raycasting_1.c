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

static double	get_wallx(t_cub *cub, int side, double perp_dist,
		double ray_angle)
{
	double	wallx;

	if (side == 0)
		wallx = cub->player->player_y + perp_dist * sin(ray_angle);
	else
		wallx = cub->player->player_x + perp_dist * cos(ray_angle);
	wallx -= floor(wallx);
	return (wallx);
}

static double	clamp_perp(double p)
{
	if (p > 1e-6)
		return (p);
	else
		return (1e-6);
}

static int	texture_x(t_cub *cub, t_ray *r, t_img *tex)
{
	double	wx;
	int		tx;

	wx = get_wallx(cub, r->side, r->perp, r->ang);
	tx = (int)(wx * (double)tex->w);
	if ((r->side == 0 && cos(r->ang) > 0) || (r->side == 1 && sin(r->ang) < 0))
		tx = tex->w - tx - 1;
	return (tx);
}

static void	draw_walls(t_cub *cub, int screen_w)
{
	int		x;
	double	invw;
	double	hpx;
	t_ray	r;

	x = -1;
	invw = 1.0 / (double)screen_w;
	hpx = (double)cub->height * TILE_SIZE;
	while (++x < screen_w)
	{
		r.cam = (double)x * invw - 0.5;
		r.ang = cub->player->player_direction + r.cam * FOV_RAD;
		r.side = 0;
		r.dist = cast_ray(cub, r.ang, &r.side, 0);
		r.perp = r.dist * cos(r.ang - cub->player->player_direction);
		r.line_h = (int)(hpx / clamp_perp(r.perp));
		r.tex = pick_texture(cub, letter_orientation(r.side, cos(r.ang),
					sin(r.ang)));
		r.texx = texture_x(cub, &r, r.tex);
		draw_vertical_line(cub, x, r.line_h, r.texx);
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
	draw_walls(cub, cub->width * TILE_SIZE);
}
