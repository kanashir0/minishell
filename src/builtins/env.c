/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:05:00 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/16 20:57:28 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(char **args, t_command *cmd)
{
	t_env	*node;

	(void)args;
	node = cmd->env_list;
	while (node)
	{
		if (node->value != NULL)
			ft_printf_fd(STDOUT_FILENO, "%s=%s\n",
				node->key, node->value);
		node = node->next;
	}
	return (0);
}
