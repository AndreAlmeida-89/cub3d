/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:43:30 by andde-so          #+#    #+#             */
/*   Updated: 2022/06/01 12:44:56 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		remain;
	int		result;
	int		base_size;
	char	c;

	base_size = 10;
	remain = n % base_size;
	result = n / base_size;
	if (n < 0)
	{
		write(fd, "-", 1);
		result *= -1;
		remain *= -1;
	}
	if (result > 0)
		ft_putnbr_fd(result, fd);
	c = remain + '0';
	write(fd, &c, 1);
}
