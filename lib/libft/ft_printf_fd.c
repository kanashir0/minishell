/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:17:16 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/16 19:45:00 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printnbr_fd(int n, int fd)
{
	long	nb;
	int		len;

	len = 0;
	if (n < 0)
	{
		len += ft_putchar_fd('-', fd);
		nb = -n;
	}
	else
		nb = n;
	if (nb >= 10)
		len += ft_printnbr_fd(nb / 10, fd);
	len += ft_putchar_fd((nb % 10) + '0', fd);
	return (len);
}

static int	printf_type_fd(va_list args, char str, int fd)
{
	int	len;

	len = 0;
	if (str == 'c')
		len += ft_putchar_fd(va_arg(args, int), fd);
	else if (str == 's')
		len += ft_putstr_fd(va_arg(args, char *), fd);
	else if (str == 'd' || str == 'i')
		len += ft_printnbr_fd(va_arg(args, int), fd);
	else if (str == '%')
		len += ft_putchar_fd('%', fd);
	return (len);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		i;

	i = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			if (*(str + 1) == '\0')
				break ;
			i += printf_type_fd(args, *++str, fd);
		}
		else
			i += ft_putchar_fd(*str, fd);
		str++;
	}
	va_end(args);
	return (i);
}
