/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:05:04 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/04 11:56:10 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../mlx_linux/mlx.h"
// #include "../libft/libft.a"
#include <stdlib.h>
#include <stdio.h> // TODO: remove

#define WIN_WIDTH 1600
#define WIN_HEIGHT 900
#define WIN_TITLE "Cub3D - 42Rio - andde-so"
#define MINIMAP_WIDTH WIN_WIDTH / 2
#define MINIMAP_HEIGHT WIN_HEIGHT
#define GAME_WIDTH WIN_WIDTH / 2
#define GAME_HEIGHT WIN_HEIGHT

typedef struct s_v2i
{
	int x;
	int y;
}t_v2i;

typedef struct s_v2f
{
	float x;
	float y;
}t_v2f;

typedef struct s_view
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	t_v2i size;
} t_view;


typedef struct s_cub3d
{
	void *mlx;
	void *mlx_win;
	t_view minimap;
	t_view game;
} t_cub3d;

typedef enum s_key
{
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	ESC_KEY = 65307
}t_key;


#endif