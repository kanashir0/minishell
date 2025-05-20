/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:48:14 by cbrito-s          #+#    #+#             */
/*   Updated: 2024/11/05 14:29:09 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*cat;

	len = ft_strlen(s1) + ft_strlen(s2);
	cat = (char *)malloc((len + 1) * sizeof(char));
	if (!cat)
		return (NULL);
	ft_strlcpy(cat, s1, ft_strlen(s1) + 1);
	ft_strlcat(cat, s2, len + 1);
	return (cat);
}
