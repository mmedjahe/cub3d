/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:01:51 by apesic            #+#    #+#             */
/*   Updated: 2025/09/09 17:01:55 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	normalize_angle(double *a)
{
	double	two_pi;

	two_pi = 2.0 * M_PI;
	while (*a < 0)
		*a += two_pi;
	while (*a >= two_pi)
		*a -= two_pi;
}

static void	if_cub_place_pos(t_cub *cub, double ca, double cb)
{
	cub->player->player_x += ca * 0.1;
	cub->player->player_y += cb * 0.1;
}

static void	if_cub_place_neg(t_cub *cub, double ca, double cb)
{
	cub->player->player_x -= ca * 0.1;
	cub->player->player_y -= cb * 0.1;
}

static void	place(int keycode, t_cub *cub)
{
	if (keycode == 65361)
	{
		cub->player->player_direction -= 0.1;
		normalize_angle(&cub->player->player_direction);
	}
	else if (keycode == 65363)
	{
		cub->player->player_direction += 0.1;
		normalize_angle(&cub->player->player_direction);
	}
}

int	handle_key(int keycode, t_cub *cub)
{
	double			a;
	double			dx;
	double			dy;

	a = cub->player->player_direction;
	dx = cos(a);
	dy = sin(a);
	if (keycode == 65307)
		ft_error("", cub);
	if (keycode == 119)
		if_cub_place_pos(cub, dx, dy);
	else if (keycode == 115)
		if_cub_place_neg(cub, dx, dy);
	else if (keycode == 100)
		if_cub_place_pos(cub, (-sin(a)), (cos(a)));
	else if (keycode == 97)
		if_cub_place_neg(cub, (-sin(a)), (cos(a)));
	place(keycode, cub);
	draw_frame(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
	return (0);
}
