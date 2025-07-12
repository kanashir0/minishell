/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:54:14 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/12 15:43:02 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_numeric(const char *str)
{
	if (!str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	builtin_exit(char **args, t_command *cmd)
{
	long	status_code;

	ft_printf_fd(STDOUT_FILENO, "exit\n");
	if (args[1] == NULL)
	{
		ft_clear_mem();
		exit(cmd->status);
	}
	if (!is_numeric(args[1]))
	{
		ft_printf_fd(STDOUT_FILENO, "exit: %s: numeric argument required\n", args[1]);
		ft_clear_mem();
		exit(2);
	}
	if (args[2])
	{
		ft_printf_fd(STDOUT_FILENO, "exit: too many arguments\n");
		cmd->status = 1;
		return (1);
	}
	status_code = ft_atol(args[1]);
	ft_clear_mem();
	exit(status_code);
}
