/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_pressed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:27:50 by andde-so          #+#    #+#             */
/*   Updated: 2024/01/05 14:29:56 by andde-so         ###   ########.fr       */
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

static void rotate(t_game *g, double rotation_speed)
{
	double old_dir_x = g->dir.x;
	double old_plane_x = g->plane.x;

	g->dir.x = g->dir.x * cos(-rotation_speed) - g->dir.y * sin(-rotation_speed);
	g->dir.y = old_dir_x * sin(-rotation_speed) + g->dir.y * cos(-rotation_speed);
	g->plane.x = g->plane.x * cos(-rotation_speed) - g->plane.y * sin(-rotation_speed);
	g->plane.y = old_plane_x * sin(-rotation_speed) + g->plane.y * cos(-rotation_speed);
}

int handle_key_pressed(int keycode, t_game *g)
{
	double move_speed = 0.4;
	double rotation_speed = 0.2;

	if (keycode == W_KEY)
		move_foward(g, move_speed);
	else if (keycode == S_KEY)
		move_foward(g, -move_speed);
	else if (keycode == D_KEY)
		rotate(g, rotation_speed);
	else if (keycode == A_KEY)
		rotate(g, -rotation_speed);
	else if (keycode == ESC_KEY)
		return (destroy_game(g));
	return (0);
}