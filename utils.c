/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:16:04 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/07 22:40:59 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_one(t_cub *cub, t_img *dst, const char *path)
{
	dst->img = mlx_xpm_file_to_image(cub->mlx.mlx, (char *)path, &dst->w,
			&dst->h);
	if (!dst->img)
		ft_error("failed to load texture (mlx_xpm_file_to_image)", cub);
	dst->addr = mlx_get_data_addr(dst->img, &dst->bpp, &dst->line_len,
			&dst->endian);
	if (!dst->addr)
		ft_error("failed to get texture data (mlx_get_data_addr)", cub);
}

void	load_textures(t_cub *cub)
{
	load_one(cub, &cub->mlx.no_tex, cub->no);
	load_one(cub, &cub->mlx.so_tex, cub->so);
	load_one(cub, &cub->mlx.we_tex, cub->we);
	load_one(cub, &cub->mlx.ea_tex, cub->ea);
}

int	close_window(t_cub *cub)
{
	ft_error("", cub);
	return (0);
}

void	cleanup_mlx(t_cub *cub)
{
	if (cub->mlx.no_tex.img)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.no_tex.img);
	}
	if (cub->mlx.so_tex.img)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.so_tex.img);
	if (cub->mlx.we_tex.img)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.we_tex.img);
	if (cub->mlx.ea_tex.img)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.ea_tex.img);
	if (cub->mlx.mlx)
	{
		if (cub->mlx.img)
			mlx_destroy_image(cub->mlx.mlx, cub->mlx.img);
		if (cub->mlx.win)
			mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		mlx_destroy_display(cub->mlx.mlx);
		free(cub->mlx.mlx);
	}
}

void	inittt(t_cub *cub)
{
	cub->player->player_x = 0;
	cub->player->player_y = 0;
	cub->mlx.no_tex = (t_img){0};
	cub->mlx.so_tex = (t_img){0};
	cub->mlx.we_tex = (t_img){0};
	cub->mlx.ea_tex = (t_img){0};
	cub->mlx.img = NULL;
	cub->mlx.win = NULL;
	cub->mlx.mlx = NULL;
}
