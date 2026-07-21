/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:41:11 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/12 15:44:54 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(t_command *cmd)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		ft_printf_fd(STDOUT_FILENO, "%s\n", tmp);
		free(tmp);
		cmd->status = 0;
	}
	else
		cmd->status = 1;
	return (0);
}
