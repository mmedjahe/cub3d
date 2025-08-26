/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:59:34 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/07/29 00:28:03 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parser(t_cub *cub, char *file)
{
    int fd;
    char *line;
    t_node *list;

    fd = open(file, O_RDONLY);
    if(fd  == -1)
        ft_error("cannot open your file", cub);
    verif_file_format(file, cub);
    line = textures_and_colors(fd, cub);
    if(!check_textures_and_colors(cub))
    {
        free(line);
        ft_error("color or texture missing", cub);
    }
    fill_map_list(&list, cub, fd, line);
    final_fill(&list, cub);
    free_list(&list);
    verif_map(cub);
    close(fd);
    return(0);
}

int sorter(char *str, t_cub *cub)
{
    int i = 0;

    while(str[i] == ' ' || str[i] == '\t')
        i++;
    if(!ft_strncmp(str + i, "F ", 2))
        return(1);
    else if(!ft_strncmp(str + i, "C ", 2))
        return(2);
    else if(!ft_strncmp(str + i, "NO ", 3))
        text_paths_stocker(&cub->NO, str + i ,cub);
    else if(!ft_strncmp(str + i, "SO ", 3))
        text_paths_stocker(&cub->SO, str + i, cub);
    else if(!ft_strncmp(str + i, "WE ", 3))
        text_paths_stocker(&cub->WE, str + i, cub);
    else if(!ft_strncmp(str + i, "EA ", 3))
        text_paths_stocker(&cub->EA, str + i, cub);
    else if(is_line_empty(str))
        return(3);
    else
        return(4);
    return(0);
}

int is_line_empty(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            return(0);
        i++;  
    }
    return(1);
}

void ground_colors_stockers(char *str, t_cub *cub)
{
    int i = 0;
    int value;

    if(cub->ground_colors[0] != -1 || cub->ground_colors[1] != -1 ||cub->ground_colors[2] != -1)
    {
        free(str);
        ft_error("ground colors appears two times", cub);
    }
    while(ft_isdigit(str[i]) != 1)
        i++;
    if(comma_counter(str+i) != 2)
    {
        free(str);
        ft_error("ground colors error", cub);
    }
    char **tab = ft_split(str+i, ',');
    if (!tab[0] || !tab[1] || !tab[2] || tab[3])
        ft_error("Wrong number of color components", cub);
    i = 0;
    while(tab[i])
    {
        value = ft_atoi(tab[i]);
        if(value < 0 || value > 255)
        {
            free(str);
            free_tab(tab);
            ft_error("ground color out of range", cub);
        }
            
        cub->ground_colors[i] = value;
        i++;
    }
    free_tab(tab);
}

void ceiling_colors_stockers(char *str, t_cub *cub)
{
    int value;
    int i ;

    if(cub->ceiling_colors[0] != -1 || cub->ceiling_colors[1] != -1 ||cub->ceiling_colors[2] != -1)
    {
        free(str);
        ft_error("ceiling colors appears two times", cub);
    }
        
    i = 0;
    while(ft_isdigit(str[i]) != 1)
        i++;
    if(comma_counter(str+i) != 2)
    {
        free(str);
        ft_error("ceiling colors error", cub);
    }
    char **tab = ft_split(str + i, ',');
    i = 0;
    while(tab[i])
    {
        value = ft_atoi(tab[i]);
        if(value < 0 || value > 255)
        {
            free(str);
            free_tab(tab);
            ft_error("ceiling color out of range", cub);
        }
            
        cub->ceiling_colors[i] = value;
        i++;
    }
    free_tab(tab);
}