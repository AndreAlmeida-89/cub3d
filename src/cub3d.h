/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:29:22 by andde-so          #+#    #+#             */
/*   Updated: 2024/01/05 13:38:32 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/libft.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <mlx.h>


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define MAP_HEIGHT 24
#define MAP_WIDTH MAP_HEIGHT
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define TEX_WIDTH 64
#define TEX_HEIGHT TEX_WIDTH

#if __APPLE__
typedef enum e_key
{
	W_KEY = 13,
	S_KEY = 1,
	D_KEY = 2,
	A_KEY = 0,
	ESC_KEY = 53
} t_key;
#else
typedef enum e_key
{
	W_KEY = 119,
	S_KEY = 115,
	D_KEY = 100,
	A_KEY = 97,
	ESC_KEY = 65307
} t_key;
#endif

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_game
{
	void *mlx;
	void *mlx_win;
	t_data img;
	double posX;
	double posY; // x and y start position
	double dirX;
	double dirY; // initial direction vector
	double planeX;
	double planeY;		// the 2d raycaster version of camera plane
	double currentTime; // time of current frame
	double oldTime;
	size_t worldMap[MAP_WIDTH][MAP_HEIGHT];
	size_t texture[8][TEX_WIDTH * TEX_HEIGHT];
} t_game;

int handle_key_pressed(int keycode, t_game *g);
int destroy_game(t_game *g);

#endif