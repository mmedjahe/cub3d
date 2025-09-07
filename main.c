/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:34:23 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/07 21:03:45 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		cub->ceiling_colors[i] = -1;
		cub->ground_colors[i] = -1;
		i++;
	}
	cub->NO = NULL;
	cub->SO = NULL;
	cub->WE = NULL;
	cub->EA = NULL;
	cub->map = NULL;
	cub->height = 0;
	cub->width = 0;
	cub->player = malloc(sizeof(t_player) * 1);
	if (!cub->player)
		ft_error("Malloc failed for player", cub);
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

void	init_mlx(t_cub *cub)
{
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		ft_error("mlx init failed", cub);
	load_textures(cub);
	cub->mlx.win = mlx_new_window(cub->mlx.mlx, cub->width * 32, cub->height
			* 32, "cub3D");
	if (!cub->mlx.win)
		ft_error("window init failed", cub);
	cub->mlx.img = mlx_new_image(cub->mlx.mlx, cub->width * 32, cub->height
			* 32);
	if (!cub->mlx.img)
		ft_error("img init failed", cub);
	cub->mlx.addr = mlx_get_data_addr(cub->mlx.img, &cub->mlx.bits_per_pixel,
			&cub->mlx.line_length, &cub->mlx.endian);
	draw_frame(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
	mlx_hook(cub->mlx.win, 2, 1L << 0, handle_key, cub);
	mlx_hook(cub->mlx.win, 17, 0L, close_window, cub);
	mlx_loop(cub->mlx.mlx);
}

int	ft_error(char *str, t_cub *cub)
{
	printf("%s\n", str);

    cleanup_mlx(cub);
    if (cub->NO) 
		free(cub->NO);
    if (cub->SO) 
		free(cub->SO);
    if (cub->WE) 
		free(cub->WE);
    if (cub->EA) 
		free(cub->EA);
    if (cub->map) 
		free_tab(cub->map);
    if (cub->player) 
		free(cub->player);
	exit(0);
}

void	verif_file_format(char *file, t_cub *cub)
{
	int	i;
	int	x;

	x = 4;
	i = 0;
	while (file[i])
		i++;
	i--;
	while (--x > 0)
		i--;
	if (strncmp(file + i, ".cub", 4))
		ft_error("file is not a .cub", cub);
}

int	main(int c, char **v)
{
	t_cub	cub;

	if (c != 2)
		printf("this program only works with one argument that is a .cub file");
	else
	{
		init_struct(&cub);
		parser(&cub, v[1]);
		check_map(&cub);
		init_mlx(&cub);
		ft_error("everything ok", &cub);
	}
	return (0);
}

