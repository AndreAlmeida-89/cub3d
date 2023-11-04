/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:00:14 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/03 17:24:02 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(CUB3D_H)
#define CUB3D_H

#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

#define BUFF_SIZE 1024
#define WIN_HEIGHT 1080
#define WIN_WIDTH 1920
#define TILE_SIZE 48
#define FOV 60
#define PLAYER_SIZE (TILE_SIZE / 2)

typedef enum e_bool
{
	FALSE,
	TRUE
} t_bool;

typedef struct s_v2
{
	float x;
	float y;
} t_v2;

typedef struct s_position
{
	t_v2 pos;
	t_v2 dir;
} t_position;

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef enum e_compass
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	NB_COMPASS
} t_compass;

typedef struct s_tile
{
	int x;
	int y;
} t_tile;

typedef enum e_key
{
	K_W = 13,
	K_A = 0,
	K_S = 1,
	K_D = 2,
	K_UP = 126,
	K_LEFT = 123,
	K_DOWN = 125,
	K_RIGHT = 124,
	K_ESC = 53
} t_key;

typedef struct t_ray
{
	t_v2 dir;
	t_v2 delta_dist;
	t_v2 side_dist;
	t_tile map;
	t_v2 step;
	float perp_wall_dist;
	int side;
	int hit;
} t_ray;


typedef struct s_game
{
	void *mlx;
	void *mlx_win;
	t_data game_screen;
	t_data player_img;
	t_data wall_img[NB_COMPASS];
	t_position player_pos;
	char **map;
	int map_width;
	int map_height;
	t_ray rays[WIN_WIDTH];
} t_game;

char **parse_file(const char *path);
int print_error(char *str, t_game *game);
void destroy_game(t_game *game);

#endif // MACRO