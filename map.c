/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:31:11 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/05 22:48:25 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_map(t_cub *cub)
{
    player_count(cub);
    is_map_closed(cub);
    if(cub->height < 3 || cub->width < 3)
        ft_error("map too short", cub);
    get_player_loc(cub);
}

void is_map_closed(t_cub *cub)
{
    int y, x;
    
    y = 0;

    char **map = rectang_map(cub, cub->map);
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            char c = map[y][x];

            if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                if (y == 0 || !map[y+1] || x == 0 || !map[y][x+1])
                {
                    free_tab(map);
                        ft_error("map not closed (border)", cub);
                }

                if (map[y-1][x] == ' ' || map[y+1][x] == ' ' ||
                    map[y][x-1] == ' ' || map[y][x+1] == ' ' ||
                    x >= (int)ft_strlen(map[y-1]) ||
                    x >= (int)ft_strlen(map[y+1]))
                    {
                        free_tab(map);
                        ft_error("map not closed ", cub);
                    }

            }
            x++;
        }
        if (cub->width < x)
            cub->width = x;
        y++;
    }
    free_tab(map);
    cub->height = y;
    printf("%d, %d\n", cub->width, cub->height);
}

void player_count(t_cub *cub)
{
    int count;
    int i;
    int x;

    count = 0;
    i = -1;
    
    while(cub->map[++i])
    {
        x = 0;
        while(cub->map[i][x])
        {
            if(cub->map[i][x] == 'N' || cub->map[i][x] == 'S' || cub->map[i][x] == 'W' || cub->map[i][x] == 'E')
                count ++;
            x++;
        }
    }
    if(count != 1)
        ft_error("map should contains only one starting position", cub);
}

void get_player_loc(t_cub *cub)
{
    int i;
    int x;

    i = -1;
    x = 0;
    while(cub->map[++i])
    {
        x = 0;
        while(cub->map[i][x])
        {
            if(cub->map[i][x] == 'N' ||cub->map[i][x] == 'S' ||cub->map[i][x] == 'E' ||cub->map[i][x] == 'W')
            {
                cub->player->player_y = (double)i + 0.5;
                cub->player->player_x = (double)x + 0.5;;
                if (cub->map[i][x] == 'N')
                    cub->player->player_direction = M_PI_2;       
                else if (cub->map[i][x] == 'S')
                    cub->player->player_direction = 3 * M_PI_2;    
                else if (cub->map[i][x] == 'E')
                    cub->player->player_direction = 0;             
                else if (cub->map[i][x] == 'W')
                    cub->player->player_direction = M_PI;     
                return;
            }
            x++;
        }
    }
}

char **rectang_map(t_cub *cub, char **original_map)
{
    size_t y;
    int i;
    int height;
    size_t width;
    char **new_map;
    size_t len;
    y = 0;
    width = ft_strlen(original_map[y]);
    while(original_map[y])
    {
        if(ft_strlen(original_map[y]) > width)
            width = ft_strlen(original_map[y]);
        y++;
    }
    height = y;
    new_map = malloc(sizeof(char *) * (height + 1));
    if(!new_map)
        ft_error("malloc failed", cub);
    i = 0;
    while(i < height)
    {
        len = ft_strlen(original_map[i]);
        new_map[i] = malloc(sizeof(char) * (width + 1));
        ft_memcpy(new_map[i], original_map[i], len);
        while(len < width)
            new_map[i][len++] = ' ';
        new_map[i][len] = '\0';
        i++;
    }
    new_map[height] = NULL;
    return(new_map);
}
