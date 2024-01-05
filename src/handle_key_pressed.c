/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_pressed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:27:50 by andde-so          #+#    #+#             */
/*   Updated: 2024/01/05 14:26:41 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static void move_foward(t_game *g, double move_speed)
{
	if (g->world_map[(int)(g->pos.x + g->dir.x * move_speed)][(int)(g->pos.y)] == 0)
		g->pos.x += g->dir.x * move_speed;
	if (g->world_map[(int)(g->pos.x)][(int)(g->pos.y + g->dir.y * move_speed)] == 0)
		g->pos.y += g->dir.y * move_speed;
}

static void rotate(t_game *g, double rotSpeed)
{
	double old_dir_x = g->dir.x;
	double old_plane_x = g->plane.x;

	g->dir.x = g->dir.x * cos(-rotSpeed) - g->dir.y * sin(-rotSpeed);
	g->dir.y = old_dir_x * sin(-rotSpeed) + g->dir.y * cos(-rotSpeed);
	g->plane.x = g->plane.x * cos(-rotSpeed) - g->plane.y * sin(-rotSpeed);
	g->plane.y = old_plane_x * sin(-rotSpeed) + g->plane.y * cos(-rotSpeed);
}

int handle_key_pressed(int keycode, t_game *g)
{
	double move_speed = 0.4;
	double rotSpeed = 0.2;

	if (keycode == W_KEY)
		move_foward(g, move_speed);
	else if (keycode == S_KEY)
		move_foward(g, -move_speed);
	else if (keycode == D_KEY)
		rotate(g, rotSpeed);
	else if (keycode == A_KEY)
		rotate(g, -rotSpeed);
	else if (keycode == ESC_KEY)
		return (destroy_game(g));
	return (0);
}