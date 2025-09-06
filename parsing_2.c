/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:25:31 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/06 19:41:52 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int comma_counter(char *str)
{
    int i;
    int count;

    count = 0;
    i = -1;
    while(str[++i])
    {
        if(str[i] == ',')
            count++;
    }
    return(count);
}

void text_paths_stocker(char **dest, char *src, t_cub *cub)
{
    int i;
    int len;
    char *s;
    
    if(*dest != NULL)
    {
        free(src);
        ft_error("same texture appears two times", cub);
    }
        
    i = 3;
    s = ft_strtrim(src, "\n");
    if(!s)
        return;
    len = ft_strlen(s + i);

    *dest = malloc(sizeof(char) * (len + 1));
    if(!*dest)
        return;
    ft_strlcpy(*dest, s + i, len + 1);
    free(s);
}

void free_tab(char **tab)
{
    int i;

    i = -1;
    while(tab[++i])
        free(tab[i]);
    free(tab);
}

int check_textures_and_colors(t_cub *cub)
{
    int i = 0;
    while(i < 3)
    {
        if(cub->ceiling_colors[i] == -1 || cub->ground_colors[i] == -1)
            return(0);
        i++;
    }
    if(!cub->NO || !cub->SO || !cub->EA || !cub->WE)
        return(0);
    return(1);
}

void verif_map(t_cub *cub)
{
    int i;
    int x;

    i = 0;
    while(cub->map[i])
    {
        x = 0;
        while (cub->map[i][x])
        {
            if(cub->map[i][x] !='0' && cub->map[i][x] !='1' && cub->map[i][x] !='N' 
            && cub->map[i][x] !='S' && cub->map[i][x] !='W' && cub->map[i][x] !='E'
        && cub->map[i][x] !=' ')
                ft_error("map contains invalid characters", cub);
            x++;
        }
        i++;
    }
}