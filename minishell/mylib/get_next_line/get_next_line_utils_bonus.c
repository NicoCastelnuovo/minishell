/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:49:20 by fahmadia          #+#    #+#             */
/*   Updated: 2023/05/30 15:06:23 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*p_dst;
	const char	*p_src;
	size_t		i;

	p_dst = (char *)dst;
	p_src = (char *)src;
	i = 0;
	if (!dst && !src && n)
		return (NULL);
	while (i < n)
	{
		p_dst[i] = p_src[i];
		i++;
	}
	return (dst);
}

char	*ft_my_strjoin(char *s1, char *s2)
{
	size_t	s1_length;
	size_t	s2_length;
	size_t	total_size;
	char	*p_new_string;
	int		i;

	i = 0;
	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	total_size = s1_length + s2_length + 1;
	p_new_string = malloc(total_size * sizeof(char));
	if (!p_new_string || (!s1 && !s2))
		return (NULL);
	ft_memcpy(p_new_string, s1, s1_length + 1);
	ft_memcpy(p_new_string + s1_length, s2, s2_length);
	p_new_string[total_size - 1] = '\0';
	free(s1);
	return (p_new_string);
}

char	*ft_my_substr(char const *s, unsigned int start, size_t len)
{
	size_t	total_size;
	char	*p_substring;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return ("");
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	total_size = (len + 1) * sizeof(char);
	p_substring = malloc(total_size);
	if (!p_substring)
		return (NULL);
	if (len + 1 > 0)
	{
		while (i < len && (s + start)[i])
		{
			p_substring[i] = (s + start)[i];
			i++;
		}
	p_substring[i] = '\0';
	}
	return (p_substring);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*p;
	size_t	i;
	char	*q;

	total_size = count * size;
	if (count != 0 && total_size / count != size)
		return (NULL);
	p = malloc(total_size);
	if (!p)
		return (NULL);
	i = 0;
	q = (char *)p;
	while (i < total_size)
	{
		q[i] = 0;
		i++;
	}
	return (p);
}
