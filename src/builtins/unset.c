/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:54:50 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/01 19:24:13 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_env_var(t_env *node, char *args, t_command *cmd)
{
	t_env	*del_node;

	while (node)
	{
		if (ft_strncmp(node->key, args, ft_strlen(args) + 1) == 0)
		{
			del_node = node;
			if (del_node->prev)
				del_node->prev->next = del_node->next;
			else
				cmd->env_list = node->next;
			if (del_node->next)
				del_node->next->prev = del_node->prev;
			untrack_pointer(del_node->key);
			untrack_pointer(del_node->value);
			untrack_pointer(del_node);
			break ;
		}
		node = node->next;
	}
}

int	unset(char **args, t_command *cmd)
{
	t_env	*node;
	int		i;

	i = 1;
	while (args[i])
	{
		node = cmd->env_list;
		clear_env_var(node, args[i], cmd);
		i++;
	}
	return (0);
}
