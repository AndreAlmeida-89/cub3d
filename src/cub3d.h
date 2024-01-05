/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:29:22 by andde-so          #+#    #+#             */
/*   Updated: 2024/01/05 14:26:41 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/libft.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <mlx.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

typedef struct s_vector
{
	double x;
	double y;
} t_vector;

typedef struct s_game
{
	void *mlx;
	void *mlx_win;
	t_data img;
	t_vector pos;
	t_vector dir;
	t_vector plane;		 // the 2d raycaster version of camera plane
	double current_time; // time of current frame
	double old_time;
	size_t world_map[MAP_WIDTH][MAP_HEIGHT];
	size_t texture[8][TEX_WIDTH * TEX_HEIGHT];
} t_game;

int handle_key_pressed(int keycode, t_game *g);
int destroy_game(t_game *g);

#endif