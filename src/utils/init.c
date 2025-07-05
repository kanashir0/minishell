/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:09:43 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/05 19:31:28 by cbrito-s         ###   ########.fr       */
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

void	init_under(t_command *cmd, char *prog)
{
	t_env	*underscore;

	underscore = new_env(ft_strdup("_"), ft_strdup(prog));
	addback_env(&cmd->env_list, underscore);
}

void	update_under(t_command *cmd, char *new_value)
{
	t_env *us;

	us = get_env(cmd->env_list, "_");
	if (us)
	{
		untrack_pointer(us->value);
		us->value = ft_strdup(new_value);
	}
	else
	{
		us = new_env(ft_strdup("_"), ft_strdup(new_value));
		addback_env(&cmd->env_list, us);
	}
}
