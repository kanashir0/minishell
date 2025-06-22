/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:15:46 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/22 14:21:53 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_swap(t_env **a, t_env **b)
{
	t_env	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	count_env(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

int	count_env_arr(t_env **environ)
{
	int	 count;

	count = 0;
	while (environ[count])
		count++;
	return (count);
}

t_env	*new_env(char *key, char *val)
{
	t_env	*node;

	node = ft_collect_mem(1, sizeof(t_env));
	node->key = ft_strdup(key);
	node->value = val;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}
