/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2f.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:35:03 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/06 21:23:22 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_v2f v2f(float x, float y)
{
	return ((t_v2f){x, y});
}

t_v2f v2f_add(t_v2f v1, t_v2f v2)
{
	return ((t_v2f){v1.x + v2.x, v1.y + v2.y});
}

t_v2f v2f_sub(t_v2f v1, t_v2f v2)
{
	return ((t_v2f){v1.x - v2.x, v1.y - v2.y});
}

t_v2f v2f_mult(t_v2f v, float n)
{
	return ((t_v2f){v.x * n, v.y * n});
}

t_v2f v2f_div(t_v2f v, float n)
{
	return ((t_v2f){v.x / n, v.y / n});
}

t_v2f v2f_normalize(t_v2f v)
{
	float magnitude;

	magnitude = sqrt(v.x * v.x + v.y * v.y);
	return ((t_v2f){v.x / magnitude, v.y / magnitude});
}