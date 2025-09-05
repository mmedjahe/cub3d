
#include "cub3d.h"

static void	normalize_angle(double *a)
{
	double	TWO_PI;

	TWO_PI = 2.0 * M_PI;
	while (*a < 0)
		*a += TWO_PI;
	while (*a >= TWO_PI)
		*a -= TWO_PI;
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
		(mlx_destroy_window(cub->mlx.mlx, cub->mlx.win), exit(0));
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
