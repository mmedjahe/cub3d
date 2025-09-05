/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:32:24 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/05 22:47:08 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "./libft/libft.h"
#include "./minilibx-linux/mlx.h"
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
# define M_PI_2 (M_PI / 2)
#endif

#ifndef FOV_DEG
# define FOV_DEG 60.0
#endif

#ifndef FOV_RAD
# define FOV_RAD (FOV_DEG * M_PI / 180.0)
#endif
#define TILE_SIZE 32



typedef struct s_player
{
    double player_y;
    double player_x;
    double player_direction;
}               t_player;

typedef struct s_mlx
{
    void *mlx;
    void *win;
    void *img;
    void *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
}               t_mlx;

typedef struct s_keys {
    int w, a, s, d;
    int left, right;
} t_keys;

typedef struct s_cub
{
    char *NO;
    char *SO;
    char *EA;
    char *WE;
    int  ground_colors[3];
    int  ceiling_colors[3];
    char **map;
    int height;
    int width;
    t_mlx mlx;
    t_player *player;
    t_keys keys;
}              t_cub;

typedef struct s_node
{
    char *line;
    struct s_node *next;
}              t_node;

int parser(t_cub *cub, char *file);
int sorter(char *str, t_cub *cub);
int is_line_empty(char *str);
void ground_colors_stockers(char *str, t_cub *cub);
void ceiling_colors_stockers(char *str, t_cub *cub);
int comma_counter(char *str);
int ft_error(char *str, t_cub *cub);
void text_paths_stocker(char **dest, char *src, t_cub *cub);
void free_tab(char **tab);
char* textures_and_colors(int fd, t_cub *cub);
int check_textures_and_colors(t_cub *cub);
void fill_map_list(t_node **list, t_cub *cub, int fd, char *line);
void add_node(t_node **node, char *line,  t_cub *cub);
void final_fill(t_node **list, t_cub *cub);
void free_list (t_node **list);
void verif_map(t_cub *cub);
void verif_file_format(char *file, t_cub *cub);
void check_map(t_cub *cub);
void player_count(t_cub *cub);
void is_map_closed(t_cub *cub);
void still_checking_if_closed(t_cub *cub);
void get_player_loc(t_cub *cub, int i);
void draw_frame(t_cub *cub);
void put_pixel(t_cub *cub, int y, int x, int color);
void draw_tile(t_cub *cub, int x, int y, int color);
int handle_key(int keycode, t_cub *cub);
int get_color(int *value_color);
int is_wall_or_void(t_cub *cub, int mx, int my);
void draw_vertical_line(t_cub *cub, int x, int start, int end, int color);

#endif
