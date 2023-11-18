/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:21:48 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/06 21:25:02 by andde-so         ###   ########.fr       */
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
	{
		cub3d->player.pos.x += cub3d->player.dir.x;
		cub3d->player.pos.y += cub3d->player.dir.y;
	}
	else if (keycode == S_KEY)
	{
		cub3d->player.pos.x -= cub3d->player.dir.x;
		cub3d->player.pos.y -= cub3d->player.dir.y;
	}
	else if (keycode == A_KEY)
	{
		cub3d->player.angle -= 0.1;
		if (cub3d->player.angle < 0)
			cub3d->player.angle += 2 * M_PI;
		cub3d->player.dir.x = cos(cub3d->player.angle) * STEP_SIZE;
		cub3d->player.dir.y = sin(cub3d->player.angle) * STEP_SIZE;
		v2f_normalize(cub3d->player.dir);
	}
	else if (keycode == D_KEY)
	{
		cub3d->player.angle += 0.1;
		if (cub3d->player.angle > 2 * M_PI)
			cub3d->player.angle -= 2 * M_PI;
		cub3d->player.dir.x = cos(cub3d->player.angle) * STEP_SIZE;
		cub3d->player.dir.y = sin(cub3d->player.angle) * STEP_SIZE;
		v2f_normalize(cub3d->player.dir);
	}
	return (0);
}

void draw_line(t_view *view, t_v2i start, t_v2i end, int color)
{
	t_v2i delta;
	t_v2i sign;
	t_v2i current;

	delta.x = abs(end.x - start.x);
	delta.y = abs(end.y - start.y);
	sign.x = start.x < end.x ? 1 : -1;
	sign.y = start.y < end.y ? 1 : -1;
	int error = delta.x - delta.y;
	current = start;
	while (current.x != end.x || current.y != end.y)
	{
		my_mlx_pixel_put(view, current.x, current.y, color);
		int error2 = error * 2;
		if (error2 > -delta.y)
		{
			error -= delta.y;
			current.x += sign.x;
		}
		if (error2 < delta.x)
		{
			error += delta.x;
			current.y += sign.y;
		}
	}
}

void draw_map(t_cub3d *cub3d)
{
	int i;
	int j;

	i = -1;
	while (++i < MAP_WIDTH)
	{
		j = -1;
		while (++j < MAP_HEIGT)
		{
			if (map[i][j] == 1)
				mlx_put_image_to_window(cub3d->mlx,
										cub3d->mlx_win,
										cub3d->wall.img,
										j * TILE_SIZE,
										i * TILE_SIZE);
			else
				mlx_put_image_to_window(cub3d->mlx,
										cub3d->mlx_win,
										cub3d->floor.img,
										j * TILE_SIZE,
										i * TILE_SIZE);
		}
	}
}

int main_loop(t_cub3d *cub3d)
{
	mlx_clear_window(cub3d->mlx, cub3d->mlx_win);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->minimap.img, 0x0000FF00, 0);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->game.img, WIN_WIDTH / 2, 0);
	draw_map(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win,
							cub3d->player.view.img,
							cub3d->player.pos.x,
							cub3d->player.pos.y);
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