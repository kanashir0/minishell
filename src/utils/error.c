/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:58:40 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/12 15:48:28 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_handler(char *msg)
{
	ft_printf_fd(STDERR_FILENO, msg);
	ft_clear_mem();
	exit(EXIT_FAILURE);
}
int	print_cmd_error(char *command, int res)
{
	if (res == 0)
	{
		ft_printf_fd(STDERR_FILENO, command);
		return (ft_printf_fd(STDERR_FILENO, ": command not found\n"), 127);
	}
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	ft_printf_fd(STDERR_FILENO, command);
	if (res == -1)
		return (ft_printf_fd(STDERR_FILENO, ": Permission denied\n"), 126);
	if (res == -2)
		return (ft_printf_fd(STDERR_FILENO, ": No such file or directory\n"), 127);
	if (res == -3)
		return (ft_printf_fd(STDERR_FILENO, ": Is a directory\n"), 126);
	return (1);
}
