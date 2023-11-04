/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:05:10 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/04 12:08:34 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_view view_init(void *mlx_ptr, t_v2i size)
{
	t_view view;

	view.img = mlx_new_image(mlx_ptr, size.x, size.y);
	view.addr = mlx_get_data_addr(view.img,
								  &view.bits_per_pixel,
								  &view.line_length,
								  &view.endian);
	view.size = size;
	return (view);
}

static void my_mlx_pixel_put(t_view *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void view_set_background_color(t_view *view, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < view->size.x)
	{
		j = -1;
		while (++j < view->size.y)
			my_mlx_pixel_put(view, i, j, color);
	}
}