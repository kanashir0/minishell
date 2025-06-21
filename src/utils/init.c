/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:09:43 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/21 16:22:05 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*get_cmd_context(t_command *cmd)
{
	static t_command	*context;

	if (cmd)
		context = cmd;
	return (context);
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = ft_collect_mem(1, sizeof(t_command));
	get_cmd_context(cmd);
	return (cmd);
}
