/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:31:11 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/08/08 00:59:40 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_map(t_cub *cub)
{
//    (void)cub;
    player_count(cub);
    is_map_closed(cub);
    still_checking_if_closed(cub);
    if(cub->height < 3 || cub->width < 3)
        ft_error("map too short", cub);
    get_player_loc(cub);
}

void is_map_closed(t_cub *cub)
{
    int i;
    int x;

    i = -1;
    while(cub->map[++i])
    {
        x = 0;
        while(cub->map[i][x] && !ft_isdigit(cub->map[i][x]))
                x++;
        if(cub->map[i][x] != '1' && cub->map[i][x + 1] != '1')
            ft_error("map is not surrounded by walls", cub);
    }
    cub->height = i;
    i = -1;
    while(cub->map[++i])
    {
        x = ft_strlen(cub->map[i]) - 1;
        if(x > cub->width)
            cub->width = x+1;
        if(cub->map[i][x] != '1' && cub->map[i][x - 1] != '1')
            ft_error("map is not surrounded by walls", cub);
    }
    // cub->screen_w = cub->width * TILE_SIZE;
    // cub->screen_h = cub->height * TILE_SIZE;

}

void still_checking_if_closed(t_cub *cub)
{
    int x;
    int i;

    i = 0;
    x = -1;
    while(cub->map[i][++x])
    {
        if(cub->map[i][x] != '1' && cub->map[i +1][x] != '1')
            ft_error("map is not surrounded by walls", cub);
    }
    while(cub->map[i])
        i++;
    i--;
    x = -1;
    while(cub->map[i][++x])
    {
        if(cub->map[i][x] != '1' && cub->map[i-1][x] != '1')
            ft_error("map is not surrounded by walls", cub);
    }
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
