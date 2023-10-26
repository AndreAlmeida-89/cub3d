/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:30:20 by andde-so          #+#    #+#             */
/*   Updated: 2022/06/01 12:50:12 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_decimal_places(int n);
static int	ft_abs(int n);

char	*ft_itoa(int n)
{
	int		len;
	char	*p;

	len = ft_decimal_places(n) + 1 + (n < 0);
	p = malloc(len);
	if (!p)
		return (NULL);
	if (n < 0)
		p[0] = '-';
	else
		p[0] = '0';
	p[len - 1] = '\0';
	while (n != 0)
	{
		p[len - 2] = '0' + ft_abs(n % 10);
		n /= 10;
		len--;
	}
	return (p);
}

static int	ft_decimal_places(int n)
{
	int	i;

	i = 0;
	if (n / 10 == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}
