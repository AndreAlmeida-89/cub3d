/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:19:19 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/03 10:19:39 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	print_error(char *str, t_game *game)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	if (game)
		destroy_game(game);
	exit(1);
}
