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

int	get_color(int *value_color)
{
	return (value_color[0] * 65536 + value_color[1] * 256 + value_color[2]);
}

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

static char	get_orientation(t_cub *cub, int x)
{
	int		screen_w;
	double	cam;
	double	ray_angle;
	int		side;
	double	ray_dir_x;
	double	ray_dir_y;

	screen_w = cub->width * TILE_SIZE;
	cam = ((double)x / (double)screen_w) - 0.5;
	ray_angle = cub->player->player_direction + cam * FOV_RAD;
	side = 0;
	cast_ray(cub, ray_angle, &side);
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	return (letter_orientation(side, ray_dir_x, ray_dir_y));
}

void	draw_vertical_line(t_cub *cub, int x, int line_h, int texX)
{
	int				screen_h;
	t_img			*tex;
	int				start;
	int				end;
	double			step;
	double			texPos;
	int				y;
	int				texY;
	unsigned int	color;

	screen_h = cub->height * TILE_SIZE;
	tex = pick_texture(cub, get_orientation(cub, x));
	start = -line_h / 2 + (cub->height * TILE_SIZE) / 2;
	end = line_h / 2 + (cub->height * TILE_SIZE) / 2;
	if (start < 0)
		start = 0;
	if (end >= screen_h)
		end = screen_h - 1;
	step = (double)tex->h / (double)line_h;
	texPos = (start - (-line_h / 2.0 + screen_h / 2.0)) * step;
	y = start;
	while (y <= end)
	{
		texY = (int)texPos;
		if (texY < 0)
			texY = 0;
		if (texY >= tex->h)
			texY = tex->h - 1;
		texPos += step;
		color = tex_px(tex, texX, texY);
		put_pixel(cub, x, y, (int)color);
		y++;
	}
}

unsigned int	tex_px(const t_img *im, int x, int y)
{
	char	*p;

	p = im->addr + y * im->line_len + x * (im->bpp / 8);
	return (*(unsigned int *)p);
}
