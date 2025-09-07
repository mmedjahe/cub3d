/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:16:04 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/07 20:27:37 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void load_one(t_cub *cub, t_img *dst, const char *path)
{
    dst->img = mlx_xpm_file_to_image(cub->mlx.mlx, (char *)path, &dst->w, &dst->h);
    if (!dst->img)
        ft_error("failed to load texture (mlx_xpm_file_to_image)", cub);
    dst->addr = mlx_get_data_addr(dst->img, &dst->bpp, &dst->line_len, &dst->endian);
    if (!dst->addr)
        ft_error("failed to get texture data (mlx_get_data_addr)", cub);
}

void load_textures(t_cub *cub)
{
    load_one(cub, &cub->mlx.no_tex, cub->NO);
    load_one(cub, &cub->mlx.so_tex, cub->SO);
    load_one(cub, &cub->mlx.we_tex, cub->WE);
    load_one(cub, &cub->mlx.ea_tex, cub->EA);
}

int close_window(t_cub *cub)
{
	ft_error("", cub);
	return(0);
}

void cleanup_mlx(t_cub *cub)
{
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