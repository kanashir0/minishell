/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:05:00 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/01 18:45:23 by cbrito-s         ###   ########.fr       */
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
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	return (0);
}
