/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2i.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:30:27 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/05 14:32:59 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_v2i v2i(int x, int y)
{
	return ((t_v2i){x, y});
}

t_v2i v2i_add(t_v2i v1, t_v2i v2)
{
	return ((t_v2i){v1.x + v2.x, v1.y + v2.y});
}

t_v2i v2i_sub(t_v2i v1, t_v2i v2)
{
	return ((t_v2i){v1.x - v2.x, v1.y - v2.y});
}

t_v2i v2i_mult(t_v2i v, int n)
{
	return ((t_v2i){v.x * n, v.y * n});
}

t_v2i v2i_div(t_v2i v, int n)
{
	return ((t_v2i){v.x / n, v.y / n});
}