/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:21:48 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/03 17:26:55 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void my_mlx_pixel_put(t_data *data, int y, int x, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_data load_img_from_path(void *mlx, char *path)
{
	t_data img;

	img.img = mlx_xpm_file_to_image(mlx,
									path,
									&img.bits_per_pixel,
									&img.line_length);
	img.addr = mlx_get_data_addr(img.img,
								 &img.bits_per_pixel,
								 &img.line_length,
								 &img.endian);
	return (img);
}

t_data circle(void *mlx, int color, int circle_radius)
{
	t_data img;
	int i;
	int j;

	img.img = mlx_new_image(mlx, circle_radius, circle_radius);
	img.addr = mlx_get_data_addr(img.img,
								 &img.bits_per_pixel,
								 &img.line_length,
								 &img.endian);
	i = -1;
	while (++i < circle_radius)
	{
		j = -1;
		while (++j < circle_radius)
		{
			if (sqrt(pow(i - circle_radius / 2, 2) + pow(j - circle_radius / 2, 2)) < circle_radius / 2)
				my_mlx_pixel_put(&img, i, j, color);
		}
	}
	return (img);
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

int ft_strlen_array(char **array)
{
	int i = -1;
	while (array[++i])
		;
	return (i);
}

int render_next_frame(void *param)
{
	t_game *game;

	game = (t_game *)param;
	mlx_clear_window(game->mlx, game->mlx_win);
	int i = -1;
	int j;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx,
										game->mlx_win,
										game->wall_img[2].img,
										j * TILE_SIZE,
										i * TILE_SIZE);
		}
	}
	mlx_put_image_to_window(game->mlx,
							game->mlx_win,
							game->player_img.img,
							game->player_pos.pos.x,
							game->player_pos.pos.y);

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
			my_mlx_pixel_put(&game->game_screen, i, x_position, line_color);
		else if (i < WIN_HEIGHT / 2)
			my_mlx_pixel_put(&game->game_screen, i, x_position, sky_color);
		else
			my_mlx_pixel_put(&game->game_screen, i, x_position, floor_color);
	}
}

void set_player_position(t_game* game)
{
	int i = -1;
	int j;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if (ft_strchr("NSEW", game->map[i][j]) != NULL)
			{
				game->player_pos.pos = (t_v2){j * TILE_SIZE + TILE_SIZE / 2, i * TILE_SIZE + TILE_SIZE / 2};
				if (game->map[i][j] == 'N')
					game->player_pos.dir = (t_v2){0, -1};
				else if (game->map[i][j] == 'S')
					game->player_pos.dir = (t_v2){0, 1};
				else if (game->map[i][j] == 'E')
					game->player_pos.dir = (t_v2){1, 0};
				else if (game->map[i][j] == 'W')
					game->player_pos.dir = (t_v2){-1, 0};
				return ;
			}
		}
	}
	print_error("Player position not found.", game);
}

void set_rays(t_game *game)
{
	
}

int main(void)
{
	t_game game;

	game.map = parse_file("maps/map0.cub");
	if (game.map == NULL)
		print_error("Map can not be parsed.", NULL);
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	game.game_screen.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	game.game_screen.addr = mlx_get_data_addr(&game.game_screen.img,
											  &game.game_screen.bits_per_pixel,
											  &game.game_screen.line_length,
											  &game.game_screen.endian);
	game.wall_img[NORTH] = load_img_from_path(game.mlx, "./img/north_texture.xpm");
	game.wall_img[EAST] = load_img_from_path(game.mlx, "./img/east_texture.xpm");
	game.wall_img[SOUTH] = load_img_from_path(game.mlx, "./img/south_texture.xpm");
	game.wall_img[WEST] = load_img_from_path(game.mlx, "./img/west_texture.xpm");
	game.player_img = circle(game.mlx, 0x00FFFFFF, PLAYER_SIZE);
	game.player_pos.pos.x = WIN_WIDTH / 2;
	game.player_pos.pos.y = WIN_HEIGHT / 2;
	game.player_pos.dir.x = 1;
	game.player_pos.dir.y = 0;
	game.map_width = ft_strlen(game.map[0]);
	game.map_height = ft_strlen_array(game.map);
	set_player_position(&game);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_hook, &game);
	mlx_loop_hook(game.mlx, render_next_frame, &game);
	mlx_loop(game.mlx);
	destroy_game(&game);
}