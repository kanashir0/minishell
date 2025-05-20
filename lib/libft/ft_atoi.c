/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:35:25 by cbrito-s          #+#    #+#             */
/*   Updated: 2024/10/31 15:55:21 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static const char	*special_character(const char *str, int *digit)
{
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*digit *= -1;
		str++;
	}
	return (str);
}

int	ft_atoi(const char *str)
{
	int	digit;
	int	result;

	digit = 1;
	result = 0;
	str = special_character(str, &digit);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * digit);
}
