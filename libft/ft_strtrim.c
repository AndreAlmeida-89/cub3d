/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:27:54 by andde-so          #+#    #+#             */
/*   Updated: 2022/05/23 14:44:27 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s1);
	while (s1[start]
		&& ft_strchr(set, s1[start]))
		start++;
	while (end > start
		&& s1[end - 1]
		&& ft_strrchr(set, s1[end - 1]))
		end--;
	return (ft_substr(s1, start, end - start));
}
