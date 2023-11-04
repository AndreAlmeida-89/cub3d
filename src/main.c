/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:21:48 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/04 11:58:55 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_view view_init(void *mlx_ptr, t_v2i size)
{
	t_view view;

	view.img = mlx_new_image(mlx_ptr, size.x, size.y);
	view.addr = mlx_get_data_addr(view.img,
								  &view.bits_per_pixel,
								  &view.line_length,
								  &view.endian);
	view.size = size;
	return (view);
}

void my_mlx_pixel_put(t_view *view, t_v2i coord, int color)
{
	char *dst;
	int offset;

	offset = (coord.y * view->line_length + coord.x * (view->bits_per_pixel / 8));
	dst = view->addr + offset;
	*(unsigned int *)dst = color;
}

void my_mlx_pixel_put2(t_view *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void set_view_background_color(t_view *view, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < view->size.x)
	{
		j = -1;
		while (++j < view->size.y)
			my_mlx_pixel_put(view, (t_v2i){i, j}, color);
	}
}

void cub3d_init(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	cub3d->mlx_win = mlx_new_window(cub3d->mlx,
									WIN_WIDTH,
									WIN_HEIGHT,
									WIN_TITLE);
	cub3d->minimap = view_init(cub3d->mlx, (t_v2i){MINIMAP_HEIGHT, MINIMAP_HEIGHT});
	cub3d->game = view_init(cub3d->mlx, (t_v2i){GAME_WIDTH, GAME_HEIGHT});
	set_view_background_color(&cub3d->game, 0x0000FF00);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->minimap.img, 0x0000FF00, 0);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->game.img, WIN_WIDTH / 2, 0);
}

void cub3d_destroy(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx, cub3d->minimap.img);
	mlx_destroy_image(cub3d->mlx, cub3d->game.img);
	mlx_destroy_window(cub3d->mlx, cub3d->mlx_win);
	exit(0);
}

int handle_key_pressed(int keycode, t_cub3d *cub3d)
{
	if (keycode == ESC_KEY)
		return (cub3d_destroy(cub3d), 0);
	else if (keycode == W_KEY)
		printf("Move foward\n");
	else if (keycode == S_KEY)
		printf("Move backward\n");
	else if (keycode == A_KEY)
		printf("Turn left\n");
	else if (keycode == D_KEY)
		printf("Turn right\n");
	return (0);
}

int main(void)
{
	t_cub3d cub3d;

	cub3d_init(&cub3d);
	mlx_hook(cub3d.mlx_win, 2, 1L << 0, handle_key_pressed, &cub3d);
	mlx_loop(cub3d.mlx);
	cub3d_destroy(&cub3d);
}