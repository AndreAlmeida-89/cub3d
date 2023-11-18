/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:05:04 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/06 21:24:12 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

// #include "../mlx_linux/mlx.h"
#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h> // TODO: remove

#define WIN_WIDTH 1024
#define WIN_HEIGHT 512
#define WIN_TITLE "Cub3D - 42Rio - andde-so"
#define MINIMAP_WIDTH WIN_WIDTH / 2
#define MINIMAP_HEIGHT WIN_HEIGHT
#define GAME_WIDTH WIN_WIDTH / 2
#define GAME_HEIGHT WIN_HEIGHT
#define MAP_HEIGT 8
#define MAP_WIDTH 8
#define MAP_SIZE MAP_HEIGT * MAP_WIDTH
#define TILE_SIZE MINIMAP_WIDTH / MAP_WIDTH
#define PLAYER_SIZE TILE_SIZE / 4
#define STEP_SIZE PLAYER_SIZE / 4
#define FOV_ANGLE M_PI / 3
#define NUM_RAYS WIN_WIDTH
#define WALL_STRIP_WIDTH 1

typedef struct s_v2i
{
	int x;
	int y;
} t_v2i;

typedef struct s_v2f
{
	float x;
	float y;
} t_v2f;

typedef struct s_view
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	t_v2i size;
} t_view;

typedef struct s_object
{
	t_view view;
	t_v2f pos;
	t_v2f dir;
	float angle;
} t_object;

typedef struct s_ray
{
	t_v2f pos;
	t_v2f dir;
	float angle;
	float distance;
} t_ray;

typedef struct s_cub3d
{
	void *mlx;
	void *mlx_win;
	t_view minimap;
	t_view game;
	t_view wall;
	t_view floor;
	t_object player;
	t_ray rays[NUM_RAYS];
} t_cub3d;

//linux keys
// typedef enum s_key
// {
// 	W_KEY = 119,
// 	A_KEY = 97,
// 	S_KEY = 115,
// 	D_KEY = 100,
// 	ESC_KEY = 65307
// } t_key;

//mac keys
typedef enum s_key
{
	W_KEY = 13,
	A_KEY = 0,
	S_KEY = 1,
	D_KEY = 2,
	ESC_KEY = 53
} t_key;

void cub3d_init(t_cub3d *cub3d);
void cub3d_destroy(t_cub3d *cub3d);

t_view view_init(void *mlx_ptr, t_v2i size, int color);
void my_mlx_pixel_put(t_view *data, int x, int y, int color);

//v2i
t_v2i v2i(int x, int y);
t_v2i v2i_add(t_v2i a, t_v2i b);
t_v2i v2i_sub(t_v2i a, t_v2i b);
t_v2i v2i_mult(t_v2i v, int n);
t_v2i v2i_div(t_v2i v, int n);

//v2f
t_v2f v2f(float x, float y);
t_v2f v2f_add(t_v2f a, t_v2f b);
t_v2f v2f_sub(t_v2f a, t_v2f b);
t_v2f v2f_mult(t_v2f v, float n);
t_v2f v2f_div(t_v2f v, float n);
t_v2f v2f_normalize(t_v2f v);

#endif