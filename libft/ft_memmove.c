/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:50:58 by andde-so          #+#    #+#             */
/*   Updated: 2022/05/21 22:23:13 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*to;
	unsigned char	*from;
	int				i;

	to = (unsigned char *)dst;
	from = (unsigned char *)src;
	if (from == to || len == 0)
		return (dst);
	if (to > from && to - from < (int)len)
	{
		i = len - 1;
		while (i >= 0)
		{
			to[i] = from[i];
			i--;
		}
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
