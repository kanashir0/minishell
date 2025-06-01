/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:09:43 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/01 17:09:49 by gyasuhir         ###   ########.fr       */
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