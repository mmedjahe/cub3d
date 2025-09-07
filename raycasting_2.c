

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
t_img *pick_texture(t_cub *cub, char orientation)
{
    if (orientation == 'n')
        return &cub->mlx.no_tex;
    if (orientation == 's')
        return &cub->mlx.so_tex;
    if (orientation == 'e')
        return &cub->mlx.ea_tex;
    return &cub->mlx.we_tex;
}

/* version texturée */
void draw_vertical_line(t_cub *cub, int x, int start, int end,
                            char orientation, int line_h, int texX)
{
    int     screen_h = cub->height * TILE_SIZE;
    t_img  *tex = pick_texture(cub, orientation);

    if (start < 0) start = 0;
    if (end >= screen_h) end = screen_h - 1;

    /* Pas vertical dans la texture (combien de texels par pixel écran) */
    double step = (double)tex->h / (double)line_h;

    /* Position initiale dans la texture :
       on veut que y=start corresponde au texel du haut du mur */
    double texPos = (start - (-line_h / 2.0 + screen_h / 2.0)) * step;

    for (int y = start; y <= end; ++y) {
        int texY = (int)texPos;
        if (texY < 0) texY = 0;
        if (texY >= tex->h) texY = tex->h - 1;
        texPos += step;

        unsigned int color = tex_px(tex, texX, texY);

        /* (optionnel) assombrir les murs “de côté” pour du relief */
        // if (side == 1) color = ((color & 0xFEFEFE) >> 1) | (color & 0xFF000000);

        put_pixel(cub, x, y, (int)color);
    }
}



unsigned int tex_px(const t_img *im, int x, int y)
{
    char *p = im->addr + y * im->line_len + x * (im->bpp / 8);
    return *(unsigned int *)p;
}
