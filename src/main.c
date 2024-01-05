/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:44:58 by andde-so          #+#    #+#             */
/*   Updated: 2024/01/05 14:26:41 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int destroy_game(t_game *g)
{
	mlx_destroy_image(g->mlx, g->img.img);
	mlx_destroy_window(g->mlx, g->mlx_win);
	exit(0);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void put_frames_per_second(t_game *g)
{
	double frameTime;
	g->old_time = g->current_time;
	g->current_time = clock();
	frameTime = (g->current_time - g->old_time) / CLOCKS_PER_SEC;
	char str[100];
	sprintf(str, "FPS: %f", 1.0 / frameTime);
	mlx_string_put(g->mlx, g->mlx_win, 10, 10, 0x00FFFFFF, str);
}

int main_loop(t_game *g)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		// calculate ray position and direction
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; // x-coordinate in camera space
		double rayDirX = g->dir.x + g->plane.x * cameraX;
		double rayDirY = g->dir.y + g->plane.y * cameraX;

		// which box of the map we're in
		int mapX = (int)g->pos.x;
		int mapY = (int)g->pos.y;

		// length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : ABS(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : ABS(1 / rayDirY);
		double perpWallDist;

		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; // was there a wall hit?
		int side;	 // was a NS or a EW wall hit?

		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (g->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - g->pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (g->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - g->pos.y) * deltaDistY;
		}
		// perform DDA
		while (hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			if (g->world_map[mapX][mapY] > 0)
				hit = 1;
		}

		// Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		// Calculate height of line to draw on screen
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		int pitch = 100;

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2 + pitch;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2 + pitch;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		// texturing calculations
		int texNum = g->world_map[mapX][mapY] - 1; // 1 subtracted from it so that texture 0 can be used!

		// calculate value of wallX
		double wallX; // where exactly the wall was hit
		if (side == 0)
			wallX = g->pos.y + perpWallDist * rayDirY;
		else
			wallX = g->pos.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		// x coordinate on the texture
		int texX = (int)(wallX * (double)(TEX_WIDTH));
		if (side == 0 && rayDirX > 0)
			texX = TEX_WIDTH - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = TEX_WIDTH - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * TEX_HEIGHT / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - pitch - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (TEX_HEIGHT - 1);
			texPos += step;
			size_t color = g->texture[texNum][TEX_HEIGHT * texY + texX];
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(&g->img, x, y, color);
		}
	}
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->img.img, 0, 0);
	put_frames_per_second(g);
	ft_bzero(g->img.addr, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
	return (0);
}

void init_textures(t_game *g)
{
	for (int x = 0; x < TEX_WIDTH; x++)
		for (int y = 0; y < TEX_HEIGHT; y++)
		{
			int xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
			// int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / TEX_HEIGHT;
			int xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
			g->texture[0][TEX_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEX_WIDTH - y); // flat red texture with black cross
			g->texture[1][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;	 // sloped greyscale
			g->texture[2][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor;				 // sloped yellow gradient
			g->texture[3][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; // xor greyscale
			g->texture[4][TEX_WIDTH * y + x] = 256 * xorcolor;								 // xor green
			g->texture[5][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16);			 // red bricks
			g->texture[6][TEX_WIDTH * y + x] = 65536 * ycolor;								 // red gradient
			g->texture[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128;				 // flat grey texture
		}
}

void init_world_map(t_game *g)
{
	const size_t world_map[MAP_WIDTH][MAP_HEIGHT] = {
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
		{4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
		{4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
		{4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
		{4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
		{4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
		{4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
		{4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
		{4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
		{4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
		{4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
		{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
		{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
		{6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
		{4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
		{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
		{4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
		{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}};

	ft_memcpy(g->world_map, world_map, sizeof(world_map));
}

int main(void)
{
	t_game g;
	init_textures(&g);
	init_world_map(&g);
	g.mlx = mlx_init();
	g.mlx_win = mlx_new_window(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	g.img.img = mlx_new_image(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	g.img.addr = mlx_get_data_addr(g.img.img,
								   &g.img.bits_per_pixel,
								   &g.img.line_length,
								   &g.img.endian);
	g.pos.x = 22.0;
	g.pos.y = 11.5;
	g.dir.x = -1.0;
	g.dir.y = 0.0;
	g.plane.x = 0.0;
	g.plane.y = 0.66;
	g.current_time = 0.0;
	g.old_time = 0.0;
	mlx_hook(g.mlx_win, 2, 1L << 0, handle_key_pressed, &g);
	mlx_hook(g.mlx_win, 17, 1L << 17, destroy_game, &g);
	mlx_loop_hook(g.mlx, main_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}