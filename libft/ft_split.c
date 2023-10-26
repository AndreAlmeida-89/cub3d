/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:51:34 by andde-so          #+#    #+#             */
/*   Updated: 2022/06/05 00:38:22 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_number_of_words(char const *s, char c);
static int	ft_word_len(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		word_len;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_number_of_words(s, c);
	res = malloc((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (j < len)
	{
		while (s[i] == c)
			i++;
		word_len = ft_word_len(s + i, c);
		res[j] = ft_substr(s, i, word_len);
		i += word_len;
		j++;
	}
	res[j] = NULL;
	return (res);
}

static int	ft_number_of_words(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s != c && *s)
				s++;
			len++;
		}
		else
			s++;
	}
	return (len);
}

static int	ft_word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}
