/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:58:40 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/24 10:10:50 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_handler(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_clear_mem();
	exit(EXIT_FAILURE);
}
int	print_cmd_error(char *command, int res)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	if (res == -1)
		return (ft_putstr_fd(": Permission denied\n", 2), 126);
	if (res == -2)
		return (ft_putstr_fd(": No such file or directory\n", 2), 127);
	if (res == -3)
		return (ft_putstr_fd(": Is a directory\n", 2), 126);
	if (res == 0)
		return (ft_putstr_fd(": command not found\n", 2), 127);
	return (1);
}
