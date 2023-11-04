/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:19:57 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/03 10:20:28 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void destroy_game(t_game *game)
{
	int i = -1;
	while (++i < NB_COMPASS)
		mlx_destroy_image(game->mlx, game->wall_img[i].img);
	mlx_destroy_image(game->mlx, game->player_img.img);
	mlx_destroy_image(game->mlx, game->game_screen.img);
	free(game->map);
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit(0);
}