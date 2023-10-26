/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:35 by andde-so          #+#    #+#             */
/*   Updated: 2022/06/04 20:36:29 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			s_len;

	s_len = ft_strlen(s);
	if (len > s_len)
		len = s_len;
	if (start > s_len)
		len = 0;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	s += start;
	ft_strlcpy(substr, s, len + 1);
	substr[len] = '\0';
	return (substr);
}
