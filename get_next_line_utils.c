/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:03:09 by atigzim           #+#    #+#             */
/*   Updated: 2025/03/01 15:07:45 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strle(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strle(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (len + 1 > 0)
	{
		((unsigned char *)dup)[len] = ((unsigned char *)s)[len];
		len--;
	}
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 == NULL && s2)
		return (ft_strdup(s2));
	else if (s2 == NULL && s1)
		return (ft_strdup(s1));
	p = (char *)malloc(sizeof(char) * ft_strle(s1) + ft_strle(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
		p[j++] = s1[i++];
	i = 0;
	while (s2[i])
		p[j++] = s2[i++];
	p[j] = '\0';
	return (p);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*p;
	int		i;

	if (!s)
		return (NULL);
	if (start >= ft_strle(s))
		return (ft_strdup(""));
	i = 0;
	if (len > ft_strle(s) - start)
		len = ft_strle(s) - start;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	check_new_line(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (-1);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
