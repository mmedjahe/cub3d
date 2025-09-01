

#include "cub3d.h"


int get_color(int *value_color)
{
    return (value_color[0] * 65536 + value_color[1] * 256 + value_color[2]);
}

int is_wall_or_void(t_cub *cub, int mx, int my)
{
    int rowlen;

    if (my < 0 || my >= cub->height || mx < 0)
        return (1);
    rowlen = (int)ft_strlen(cub->map[my]);
    if (mx >= rowlen)
        return (1);
    char c = cub->map[my][mx];
    return (c == '1' || c == ' ' || c == '\t');
}

void draw_vertical_line(t_cub *cub, int x, int start, int end, int color)
{
    int screen_h;
    int y;

    screen_h = cub->height * TILE_SIZE;
    if (start < 0)
       start = 0;
    if (end >= screen_h)
        end = screen_h - 1;
    y = start;
    while (y <= end)
    {
        put_pixel(cub, x, y, color);
        y++;
    }
}
