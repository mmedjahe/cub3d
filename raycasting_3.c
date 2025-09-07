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

double	cast_ray(t_cub *cub, double ray_angle, int *out_side)
{
	double	posX;
	double	posY;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	double	sideDistX;
	double	sideDistY;
	int		hit;
	int		side;
	int		safety;
	double	perp;

	posX = cub->player->player_x + 0.5;
	posY = cub->player->player_y + 0.5;
	rayDirX = cos(ray_angle);
	rayDirY = sin(ray_angle);
	mapX = (int)posX;
	mapY = (int)posY;
	if (rayDirX == 0.0)
		deltaDistX = 1e30;
	else
		deltaDistX = fabs(1.0 / rayDirX);
	if (rayDirY == 0.0)
		deltaDistY = 1e30;
	else
		deltaDistY = fabs(1.0 / rayDirY);
	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	}
	hit = 0;
	side = 0;
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
	if (side == 0)
		perp = (mapX - posX + (1 - stepX) / 2.0)
			/ (rayDirX == 0.0 ? 1e-9 : rayDirX);
	else
		perp = (mapY - posY + (1 - stepY) / 2.0)
			/ (rayDirY == 0.0 ? 1e-9 : rayDirY);
	if (out_side)
		*out_side = side;
	if (perp < 1e-6)
		perp = 1e-6;
	return (fabs(perp));
}
