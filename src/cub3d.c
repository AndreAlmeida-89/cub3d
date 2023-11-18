/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:03:10 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/06 21:21:33 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cub3d_init(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	cub3d->mlx_win = mlx_new_window(cub3d->mlx,
									WIN_WIDTH,
									WIN_HEIGHT,
									WIN_TITLE);
	cub3d->minimap = view_init(cub3d->mlx, (t_v2i){MINIMAP_HEIGHT, MINIMAP_HEIGHT}, 0x000000);
	cub3d->game = view_init(cub3d->mlx, (t_v2i){GAME_WIDTH, GAME_HEIGHT}, 0xFFFFFF);
	cub3d->wall = view_init(cub3d->mlx, (t_v2i){TILE_SIZE, TILE_SIZE}, 0xFF0000);
	cub3d->floor = view_init(cub3d->mlx, (t_v2i){TILE_SIZE, TILE_SIZE}, 0xFFFF00);
	cub3d->player = (t_object){
		.view = view_init(cub3d->mlx, (t_v2i){PLAYER_SIZE, PLAYER_SIZE}, 0xFF00FF),
		.pos = (t_v2f){MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2},
		.dir = (t_v2f){1.0, 0.0}};
	cub3d->player.angle = atan2(cub3d->player.dir.y, cub3d->player.dir.x);
}

void cub3d_destroy(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx, cub3d->minimap.img);
	mlx_destroy_image(cub3d->mlx, cub3d->game.img);
	mlx_destroy_image(cub3d->mlx, cub3d->player.view.img);
	mlx_destroy_image(cub3d->mlx, cub3d->floor.img);
	mlx_destroy_image(cub3d->mlx, cub3d->wall.img);
	mlx_destroy_window(cub3d->mlx, cub3d->mlx_win);
	exit(0);
}