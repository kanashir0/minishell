/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:23:54 by cbrito-s          #+#    #+#             */
/*   Updated: 2024/10/23 11:31:58 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*source;

	if (dest == src || n == 0)
		return (dest);
	dst = (unsigned char *)dest;
	source = (const unsigned char *)src;
	if (dst > source && dst < source + n)
	{
		dst += n;
		source += n;
		while (n--)
			*--dst = *--source;
		return (dest);
	}
	while (n--)
		*dst++ = *source++;
	return (dest);
}
