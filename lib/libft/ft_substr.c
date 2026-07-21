/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:31:57 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/05/29 18:56:47 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*sub;

	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	if (size - start < len)
		len = size - start;
	sub = ft_collect_mem(sizeof(char), len + 1);
	if (!sub)
		return (NULL);
	ft_memmove(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
