/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:56:29 by atigzim           #+#    #+#             */
/*   Updated: 2025/03/01 17:44:44 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char **buffer)
{
	char	*str;
	int		bytes;
	int		i;
	char	*tmp;

	str = NULL;
	i = -1;
	while (i == -1)
	{
		bytes = read(fd, *buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (NULL);
		if (bytes == 0)
			break ;
		(*buffer)[bytes] = '\0';
		if (!str)
			str = ft_strjoin(str, "");
		tmp = str;
		str = ft_strjoin(str, *buffer);
		i = check_new_line(*buffer);
		free(tmp);
	}
	return (str);
}

int	cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*handle_no_newline(char **full_buffer, int fd, char **buffer)
{
	char	*str;
	char	*tmp;
	char	*line;
	int		i;

	str = read_line(fd, buffer);
	if (!str)
	{
		if (*full_buffer && cmp(*full_buffer, ""))
		{
			line = ft_strdup(*full_buffer);
			free(*full_buffer);
			*full_buffer = NULL;
			return (line);
		}
		return (NULL);
	}
	tmp = ft_strjoin((*full_buffer), str);
	(free(*full_buffer), free(str));
	i = check_new_line(tmp);
	line = ft_substr(tmp, 0, i + 1);
	(*full_buffer) = ft_substr(tmp, i + 1, ft_strle(tmp) - (i - 1));
	free(tmp);
	return (line);
}

char	*append_buffer(char **full_buffer, int fd, char **buffer)
{
	int		i;
	char	*tmp;
	char	*line;

	i = check_new_line(*full_buffer);
	if (i != -1)
	{
		line = ft_substr((*full_buffer), 0, i + 1);
		tmp = (*full_buffer);
		(*full_buffer) = ft_substr((*full_buffer), i + 1,
				ft_strle((*full_buffer)) + (i + 1));
		free(tmp);
	}
	else
	{
		line = handle_no_newline(full_buffer, fd, buffer);
	}
	return (line);
}

char	*process_line(int fd, char **buffer, char **full_buffer)
{
	char	*line;
	char	*temp;
	int		index;

	line = read_line(fd, buffer);
	if (!line)
		return (NULL);
	index = check_new_line(line);
	if (index == -1)
	{
		if (ft_strle(line) > 0)
			index = ft_strle(line);
	}
	temp = line;
	line = ft_substr(temp, 0, index + 1);
	*full_buffer = ft_substr(temp, index + 1, ft_strle(temp) - (index + 1));
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*full_buffer;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647 || fd >= 1024)
	{
		if (full_buffer)
			free(full_buffer);
		return (NULL);
	}
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!full_buffer)
		line = process_line(fd, &buffer, &full_buffer);
	else
		line = append_buffer(&full_buffer, fd, &buffer);
	return (free(buffer), line);
}

// int main()
// {
// 	int fd = open("abdo.txt", O_RDONLY);
// 		char *f;
// 	while((f = get_next_line(3)) != NULL)
// 	{
// 		printf("%s",f);
// 		free(f);
// 	}
// 	close(fd);
// }