/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:12:55 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/05/29 18:56:40 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_arr(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		untrack_pointer(arr[i]);
		i++;
	}
	untrack_pointer(arr);
}

static size_t	word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	*get_word(char const *s, char c)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = word_len(s, c);
	str = ft_collect_mem(1, len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = *s;
		s++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static size_t	word_count(char const *s, char c)
{
	size_t	cont;

	cont = 0;
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
		{
			while (*s != c && *s != '\0')
				s++;
			cont++;
		}
	}
	return (cont);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**arr;

	if (!s)
		return (NULL);
	arr = ft_collect_mem(sizeof(char *), word_count(s, c) + 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			arr[i] = get_word(s, c);
			if (!arr[i])
				return (free_arr(arr, i), NULL);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	arr[i] = NULL;
	return (arr);
}
