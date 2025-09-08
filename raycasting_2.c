/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:49:01 by apesic            #+#    #+#             */
/*   Updated: 2025/09/07 21:59:59 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall_or_void(t_cub *cub, int mx, int my)
{
	int		rowlen;
	char	c;

	if (my < 0 || my >= cub->height || mx < 0)
		return (1);
	rowlen = (int)ft_strlen(cub->map[my]);
	if (mx >= rowlen)
		return (1);
	c = cub->map[my][mx];
	return (c == '1' || c == ' ' || c == '\t');
}

static char	get_orientation(t_cub *cub, int x)
{
	int		screen_w;
	double	cam;
	double	ray_angle;
	int		side;

	screen_w = cub->width * TILE_SIZE;
	cam = ((double)x / (double)screen_w) - 0.5;
	ray_angle = cub->player->player_direction + cam * FOV_RAD;
	side = 0;
	cast_ray(cub, ray_angle, &side, 0);
	return (letter_orientation(side, cos(ray_angle), sin(ray_angle)));
}

static int	screen_h(const t_cub *c)
{
	return (c->height * TILE_SIZE);
}

void	draw_vertical_line(t_cub *cub, int x, int line_h, int texX)
{
	int		sh;
	t_vline	v;
	int		ty;

	sh = screen_h(cub);
	v.tex = pick_texture(cub, get_orientation(cub, x));
	v.start = -line_h / 2 + sh / 2;
	v.end = line_h / 2 + sh / 2;
	if (v.start < 0)
		v.start = 0;
	if (v.end >= sh)
		v.end = sh - 1;
	v.step = (double)v.tex->h / (double)line_h;
	v.pos = (v.start - (-line_h / 2.0 + sh / 2.0)) * v.step;
	v.y = v.start;
	while (++v.y <= v.end)
	{
		ty = (int)v.pos;
		if (ty < 0)
			ty = 0;
		else if (ty >= v.tex->h)
			ty = v.tex->h - 1;
		put_pixel(cub, x, v.y, (int)tex_px(v.tex, texX, ty));
		v.pos += v.step;
	}
}

unsigned int	tex_px(const t_img *im, int x, int y)
{
	char	*p;

	p = im->addr + y * im->line_len + x * (im->bpp / 8);
	return (*(unsigned int *)p);
}
