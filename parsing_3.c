/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:27:48 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/07/30 00:44:24 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char* textures_and_colors(int fd, t_cub *cub)
{
    char *line;
    int result;
    
    result = 0;
    while((line = get_next_line(fd)))
    {
        result = sorter(line, cub);
        if(result == 1)
            ground_colors_stockers(line, cub);
        else if(result == 2)
            ceiling_colors_stockers(line, cub);
        else if(result == 3)
        {
            free(line);
            continue;
        }
        else if(result == 4)
            return(line);
        free(line);
    }
    return(NULL);
}

void fill_map_list(t_node **list, t_cub *cub, int fd, char *line)
{
    t_node *first;
    
    first = malloc(sizeof(t_node)  * 1);
    if(!first)
        ft_error("maloc failed", cub);
    first->line = ft_strtrim(line, "\n");
    if(!first->line)
    {
        free(line);
        free(first);
        ft_error("error during map init", cub);
    }
    first->next= NULL;
    free(line);
    *list = first;
    while((line = get_next_line(fd)))
    {
        add_node(list, line, cub);
        free(line);
    }
}

void add_node(t_node **list, char *line, t_cub *cub)
{
    t_node *new;
    t_node *tmp;

    new = malloc(sizeof(t_node) * 1);
    tmp = *list;
    while(tmp->next)
        tmp = tmp->next;
    new->line = ft_strtrim(line, "\n");
    if(!new->line)
    {
        free_list(list);
        ft_error("error during map init", cub);
    }
    new->next = NULL;
    tmp->next = new;
}

void final_fill(t_node **list, t_cub *cub)
{
    t_node *tmp_count;
    int count;
    t_node *tmp;
    int i;

    i = 0;
    count = 0;
    tmp_count = *list;
    while(tmp_count)
    {
        count++;
        tmp_count = tmp_count->next;
    }
    cub->map = malloc(sizeof(char *) * (count + 1));
    tmp = *list;
    while(tmp)
    {
        cub->map[i] = ft_strdup(tmp->line);
        i++;
        tmp = tmp->next;
    }
    cub->map[i] = NULL;
}

void free_list (t_node **list)
{
    t_node *tmp;
    while(*list)
    {
        tmp = (*list)->next;
        free((*list)->line);
        free(*list);
        *list = tmp;
    }
}