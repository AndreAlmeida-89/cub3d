/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:21:48 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/04 14:32:41 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map[MAP_WIDTH][MAP_HEIGT] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}};

int handle_key_pressed(int keycode, t_cub3d *cub3d)
{
	if (keycode == ESC_KEY)
		return (cub3d_destroy(cub3d), 0);
	else if (keycode == W_KEY)
		cub3d->player.pos.y -= 5;
	else if (keycode == S_KEY)
		cub3d->player.pos.y += 5;
	else if (keycode == A_KEY)
		cub3d->player.pos.x -= 5;
	else if (keycode == D_KEY)
		cub3d->player.pos.x += 5;
	return (0);
}

void draw_map(t_cub3d *cub3d)
{
	int i;
	int j;

	i = 0;
	while (i < MAP_WIDTH)
	{
		j = 0;
		while (j < MAP_HEIGT)
		{
			if (map[i][j] == 1)
				mlx_put_image_to_window(cub3d->mlx,
										cub3d->mlx_win,
										cub3d->floor.img,
										i + TILE_SIZE,
										j + TILE_SIZE);
			else
				mlx_put_image_to_window(cub3d->mlx,
										cub3d->mlx_win,
										cub3d->floor.img,
										i,
										j);
			j++;
		}
		i++;
	}

}

int main_loop(t_cub3d *cub3d)
{
	mlx_clear_window(cub3d->mlx, cub3d->mlx_win);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->minimap.img, 0x0000FF00, 0);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->game.img, WIN_WIDTH / 2, 0);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win,
							cub3d->player.view.img,
							cub3d->player.pos.x,
							cub3d->player.pos.y);
	draw_map(cub3d);
	return (0);
}

int main(void)
{
	t_cub3d cub3d;

	cub3d_init(&cub3d);
	mlx_hook(cub3d.mlx_win, 2, 1L << 0, handle_key_pressed, &cub3d);
	mlx_loop_hook(cub3d.mlx, main_loop, &cub3d);
	mlx_loop(cub3d.mlx);
	cub3d_destroy(&cub3d);
}