/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:21:48 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/01 16:57:18 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <math.h>

#define WIN_HEIGHT 1080
#define WIN_WIDTH 1920
#define MAP_HEIGHT 9
#define MAP_WIDTH 16
#define TILE_SIZE 120
#define PLAYER_SIZE (TILE_SIZE / 4)

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

typedef struct s_game
{
	t_data *game_screen;
	t_data *player_img;
	t_data *wall_img;
	void *mlx;
	void *mlx_win;
	t_position player_pos;
	char **map;
} t_game;

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

void my_mlx_pixel_put(t_data *data, int y, int x, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_data *square_tile(void *mlx, int color)
{
	t_data *img;
	int i;
	int j;

	img = malloc(sizeof(t_data));
	if (!img)
		return (NULL);

	img->img = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	img->addr = mlx_get_data_addr(img->img,
								  &img->bits_per_pixel,
								  &img->line_length,
								  &img->endian);
	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
			my_mlx_pixel_put(img, i, j, color);
	}
	return (img);
}

t_data *circle(void *mlx, int color, int circle_radius)
{
	t_data *img;
	int i;
	int j;

	img = malloc(sizeof(t_data));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx, circle_radius, circle_radius);
	img->addr = mlx_get_data_addr(img->img,
								  &img->bits_per_pixel,
								  &img->line_length,
								  &img->endian);
	i = -1;
	while (++i < circle_radius)
	{
		j = -1;
		while (++j < circle_radius)
		{
			if (sqrt(pow(i - circle_radius / 2, 2) + pow(j - circle_radius / 2, 2)) < circle_radius / 2)
				my_mlx_pixel_put(img, i, j, color);
		}
	}
	return (img);
}

void destroy_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	if (game->wall_img)
		free(game->wall_img);
	if (game->player_img)
		free(game->player_img);
	if (game->game_screen)
		free(game->game_screen);
	int i = -1;
	while (++i < MAP_HEIGHT)
		free(game->map[i]);
	free(game->map);
	exit(0);
}

void move_player(t_game *game, t_key key)
{
	if (key == K_W) // move foward
	{
		game->player_pos.pos.x += game->player_pos.dir.x * 10;
		game->player_pos.pos.y += game->player_pos.dir.y * 10;
	}
	if (key == K_A) // rotate left
	{
		game->player_pos.dir = (t_v2){game->player_pos.dir.x * cos(-0.1) - game->player_pos.dir.y * sin(-0.1),
									  game->player_pos.dir.x * sin(-0.1) + game->player_pos.dir.y * cos(-0.1)};
	}
	if (key == K_S) // move backward
	{
		game->player_pos.pos.x -= game->player_pos.dir.x * 10;
		game->player_pos.pos.y -= game->player_pos.dir.y * 10;
	}
	if (key == K_D) // rotate right
	{
		game->player_pos.dir = (t_v2){game->player_pos.dir.x * cos(0.1) - game->player_pos.dir.y * sin(0.1),
									  game->player_pos.dir.x * sin(0.1) + game->player_pos.dir.y * cos(0.1)};
	}
}

void draw_radius_to_player(t_game *game)
{
	t_data *player_image = game->player_img;
	int radius_size = PLAYER_SIZE / 2;
	float angle;
	int i;
	// draw player radius
	angle = atan2(game->player_pos.dir.y, game->player_pos.dir.x);
	i = -1;
	while (++i < radius_size)
	{
		my_mlx_pixel_put(player_image, radius_size + i * sin(angle), radius_size + i * cos(angle), 0x00FF0000);
	}
}

int key_hook(int keycode, void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (keycode == K_ESC)
		destroy_game(game);
	else if (keycode == K_W || keycode == K_A || keycode == K_S || keycode == K_D)
		move_player(game, keycode);
	else
		printf("keycode: %d\n", keycode);
	return (0);
}

int render_next_frame(void *param)
{
	t_game *game;

	game = (t_game *)param;
	mlx_clear_window(game->mlx, game->mlx_win);
	int i = -1;
	int j;
	while (++i < MAP_HEIGHT)
	{
		j = -1;
		while (++j < MAP_WIDTH)
		{
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx,
										game->mlx_win,
										game->wall_img->img,
										j * TILE_SIZE,
										i * TILE_SIZE);
		}
	}
	mlx_put_image_to_window(game->mlx,
							game->mlx_win,
							game->player_img->img,
							game->player_pos.pos.x,
							game->player_pos.pos.y);

	draw_radius_to_player(game);
	return (0);
}


void render_vertical_line(t_game *game, int x_position, int height)
{
	int sky_color = 0x00FF0000;
	int floor_color = 0x000000FF;
	int line_color = 0x00FFFFFF;

	int i = -1;
	while (++i < WIN_HEIGHT)
	{
		if (i < height)
			my_mlx_pixel_put(game->game_screen, i, x_position, line_color);
		else if (i < WIN_HEIGHT / 2)
			my_mlx_pixel_put(game->game_screen, i, x_position, sky_color);
		else
			my_mlx_pixel_put(game->game_screen, i, x_position, floor_color);
	}
}

int main(void)
{
	t_game game;

	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	game.game_screen = malloc(sizeof(t_data));
	if (!game.game_screen)
		return (0);
	game.game_screen->img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	game.game_screen->addr = mlx_get_data_addr(game.game_screen->img,
											   &game.game_screen->bits_per_pixel,
											   &game.game_screen->line_length,
											   &game.game_screen->endian);

	// game.player_img = circle(game.mlx, 0x00FFFFFF, PLAYER_SIZE);
	// game.wall_img = square_tile(game.mlx, 0x0000FF00);
	// game.player_pos.pos.x = WIN_WIDTH / 2;
	// game.player_pos.pos.y = WIN_HEIGHT / 2;
	// game.player_pos.dir.x = 1;
	// game.player_pos.dir.y = 0;
	// game.map = malloc(sizeof(char *) * MAP_HEIGHT);
	// if (!game.map)
	// 	return (0);
	// int i = -1;
	// while (++i < MAP_HEIGHT)
	// {
	// 	game.map[i] = malloc(sizeof(char) * MAP_WIDTH);
	// 	if (!game.map[i])
	// 		return (0);
	// }
	// game.map[0] = "1111111111111111";
	// game.map[1] = "1100000000000111";
	// game.map[2] = "1100000000011111";
	// game.map[3] = "1000010000000011";
	// game.map[4] = "1000010000011111";
	// game.map[5] = "1000000011111111";
	// game.map[6] = "1000000011111111";
	// game.map[7] = "1110000000000011";
	// game.map[8] = "1111111111111111";

	// // mlx_key_hook(game.mlx_win, key_hook, &game);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_hook, &game);
	// mlx_loop_hook(game.mlx, render_next_frame, &game);
	int j = -1;
	while (++j < WIN_WIDTH)
	{
		render_vertical_line(&game, j, WIN_HEIGHT - j);
	}


	mlx_put_image_to_window(game.mlx,
							game.mlx_win,
							game.game_screen->img,
							0,
							0);

	mlx_loop(game.mlx);
	destroy_game(&game);
}