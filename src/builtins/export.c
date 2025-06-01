/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:38:54 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/05/30 16:14:59 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	export(char **args, t_command *cmd)
{
	t_env	*node;

	node = cmd->env_list;
	if (!args[1])
	{
		printf("declare -x %s", node->key);
		if (node->value)
			printf("=\"%s\"", node->value);
		printf("\n");
	}
	return (0);
}
