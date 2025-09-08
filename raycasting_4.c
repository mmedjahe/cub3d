/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycating_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:55:35 by apesic            #+#    #+#             */
/*   Updated: 2025/09/07 21:56:21 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline double	inv0(double v, double big)
{
	if (v == 0.0)
		return (big);
	else
		return (fabs(1.0 / v));
}

static inline void	dda_init_dir(t_cub *c, double a, t_dda *d)
{
	d->px = c->player->player_x + 0.5;
	d->py = c->player->player_y + 0.5;
	d->dx = cos(a);
	d->dy = sin(a);
	d->mx = (int)d->px;
	d->my = (int)d->py;
	d->ddx = inv0(d->dx, 1e30);
	d->ddy = inv0(d->dy, 1e30);
}

static inline void	dda_init_step(t_cub *c, double ray_angle, t_dda *d)
{
	dda_init_dir(c, ray_angle, d);
	if (d->dx < 0)
	{
		d->sx = -1;
		d->sdx = (d->px - d->mx) * d->ddx;
	}
	else
	{
		d->sx = 1;
		d->sdx = (d->mx + 1.0 - d->px) * d->ddx;
	}
	if (d->dy < 0)
	{
		d->sy = -1;
		d->sdy = (d->py - d->my) * d->ddy;
	}
	else
	{
		d->sy = 1;
		d->sdy = (d->my + 1.0 - d->py) * d->ddy;
	}
	d->side = 0;
	d->safety = c->width * c->height * 4;
}

static inline int	dda_step_hit(t_cub *c, t_dda *d)
{
	if (d->sdx < d->sdy)
	{
		d->sdx += d->ddx;
		d->mx += d->sx;
		d->side = 0;
	}
	else
	{
		d->sdy += d->ddy;
		d->my += d->sy;
		d->side = 1;
	}
	return (is_wall_or_void(c, d->mx, d->my));
}

double	cast_ray(t_cub *cub, double ray_angle, int *out_side, int hit)
{
	t_dda	d;
	double	perp;

	dda_init_step(cub, ray_angle, &d);
	while (!hit && d.safety-- > 0)
		hit = dda_step_hit(cub, &d);
	if (d.side == 0)
	{
		if (d.dx == 0.0)
			perp = (d.mx - d.px + (1 - d.sx) / 2.0) / 1e-9;
		else
			perp = (d.mx - d.px + (1 - d.sx) / 2.0) / d.dx;
	}
	else
	{
		if (d.dy == 0.0)
			perp = (d.my - d.py + (1 - d.sy) / 2.0) / 1e-9;
		else
			perp = (d.my - d.py + (1 - d.sy) / 2.0) / d.dy;
	}
	if (out_side)
		*out_side = d.side;
	if (perp < 1e-6)
		perp = 1e-6;
	return (fabs(perp));
}
