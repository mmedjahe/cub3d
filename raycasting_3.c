/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycating_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:55:35 by apesic            #+#    #+#             */
/*   Updated: 2025/09/07 21:56:21 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	letter_orientation(int side, double ray_dir_x, double ray_dir_y)
{
	char	orientation;

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

t_img	*pick_texture(t_cub *cub, char orientation)
{
	if (orientation == 'n')
		return (&cub->mlx.no_tex);
	if (orientation == 's')
		return (&cub->mlx.so_tex);
	if (orientation == 'e')
		return (&cub->mlx.ea_tex);
	return (&cub->mlx.we_tex);
}

int	get_color(int *value_color)
{
	return (value_color[0] * 65536 + value_color[1] * 256 + value_color[2]);
}
