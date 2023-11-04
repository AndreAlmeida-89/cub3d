/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andde-so <andde-so@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:18:19 by andde-so          #+#    #+#             */
/*   Updated: 2023/11/03 10:28:31 by andde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_extention(const char *path, const char *extension)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(path);
	j = ft_strlen(extension);
	while (path[--i] && extension[--j])
		if (path[i] != extension[j])
			return (0);
	while (path[--i])
		if (path[i] == '.')
			return (0);
	return (1);
}

static int	contains_empty_line(char *str)
{
	return (
		str[0] == '\n'
		|| str[ft_strlen(str) - 1] == '\n'
		|| ft_strnstr(str, "\n\n", ft_strlen(str)) != NULL
	);
}

static char	*read_file(const char *path)
{
	int			fd;
	char		buffer[BUFF_SIZE + 1];
	char		*result;
	char		*temp;
	ssize_t		bytes;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		print_error("Path can not be open.", NULL);
	result = ft_strdup("");
	while (1)
	{
		bytes = read(fd, buffer, BUFF_SIZE);
		if (bytes == -1 && close(fd) == 0)
			print_error("File can not be read.", NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(result, buffer);
		free(result);
		result = temp;
	}
	close(fd);
	return (result);
}

char	**parse_file(const char *path)
{
	char	**map;
	char	*file_content;

	if (!check_extention(path, ".cub"))
		print_error("Invalid file extension.", NULL);
	file_content = read_file(path);
	if (contains_empty_line(file_content))
	{
		free(file_content);
		print_error("Map contains empty line.", NULL);
	}
	map = ft_split(file_content, '\n');
	free(file_content);
	// if (!*map)
	// 	print_error("Empty file.", map);
	return (map);
}
