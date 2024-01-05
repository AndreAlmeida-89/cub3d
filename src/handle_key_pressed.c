/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_pressed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:27:50 by andde-so          #+#    #+#             */
/*   Updated: 2024/01/05 13:39:54 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int handle_key_pressed(int keycode, t_game *g)
{
	double moveSpeed = 0.1; //the constant value is in squares/second
	double rotSpeed = 0.05; //the constant value is in radians/second

	// move forward if no wall in front of you
	if (keycode == W_KEY)
	{
		if (g->worldMap[(int)(g->posX + g->dirX * moveSpeed)][(int)(g->posY)] == 0)
			g->posX += g->dirX * moveSpeed;
		if (g->worldMap[(int)(g->posX)][(int)(g->posY + g->dirY * moveSpeed)] == 0)
			g->posY += g->dirY * moveSpeed;
	}
	// move backwards if no wall behind you
	if (keycode == S_KEY)
	{
		if (g->worldMap[(int)(g->posX - g->dirX * moveSpeed)][(int)(g->posY)] == 0)
			g->posX -= g->dirX * moveSpeed;
		if (g->worldMap[(int)(g->posX)][(int)(g->posY - g->dirY * moveSpeed)] == 0)
			g->posY -= g->dirY * moveSpeed;
	}
	// rotate to the right
	if (keycode == D_KEY)
	{
		// both camera direction and camera plane must be rotated
		double oldDirX = g->dirX;
		g->dirX = g->dirX * cos(-rotSpeed) - g->dirY * sin(-rotSpeed);
		g->dirY = oldDirX * sin(-rotSpeed) + g->dirY * cos(-rotSpeed);
		double oldPlaneX = g->planeX;
		g->planeX = g->planeX * cos(-rotSpeed) - g->planeY * sin(-rotSpeed);
		g->planeY = oldPlaneX * sin(-rotSpeed) + g->planeY * cos(-rotSpeed);
	}
	// rotate to the left
	if (keycode == A_KEY)
	{
		// both camera direction and camera plane must be rotated
		double oldDirX = g->dirX;
		g->dirX = g->dirX * cos(rotSpeed) - g->dirY * sin(rotSpeed);
		g->dirY = oldDirX * sin(rotSpeed) + g->dirY * cos(rotSpeed);
		double oldPlaneX = g->planeX;
		g->planeX = g->planeX * cos(rotSpeed) - g->planeY * sin(rotSpeed);
		g->planeY = oldPlaneX * sin(rotSpeed) + g->planeY * cos(rotSpeed);
	}
	if (keycode == ESC_KEY)
		return (destroy_game(g));
	return (0);
}