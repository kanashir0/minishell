/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:29:00 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/22 15:12:36 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*get_env(t_env *env_list, char *key)
{
	t_env	*node;
	int		len;

	len = ft_strlen(key) + 1;
	node = env_list;
	while (node)
	{
		if (ft_strncmp(node->key, key, len) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

t_env	**env_list_copy(t_env *env_list)
{
	t_env	**env_copy;
	int		i;
	int		len_env;

	len_env = count_env(env_list);
	env_copy = ft_collect_mem(sizeof(t_env *), len_env + 1);
	if (!env_copy)
		perror("malloc");
	i = 0;
	while (env_list)
	{
		env_copy[i++] = env_list;
		env_list = env_list->next;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

t_env	**env_list_ord(t_env **environ, int count)
{
	int		swap;
	int		i;
	int		len;

	if (!environ || count < 2)
		return (environ);
	while (42)
	{
		swap = 0;
		i = 0;
		while (i < count - 1)
		{
			len = ft_strlen(environ[i]->key);
			if (ft_strncmp(environ[i]->key, environ[i + 1]->key, len) > 0)
			{
				ft_swap(&environ[i], &environ[i + 1]);
				swap = 1;
			}
			i++;
		}
		if (swap == 0)
			break ;
	}
	return (environ);
}

void	addback_env(t_env **head, t_env *new_node)
{
	t_env	*last;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}

void	init_env(t_command *cmd, char **envp)
{
	int		i;
	char	**tmp;
	t_env	*new_node;

	i = 0;
	cmd->env_list = NULL;
	while (envp[i])
	{
		tmp = ft_split(envp[i++], '=');
		if (tmp && tmp[0] && tmp[1])
		{
			new_node = ft_collect_mem(1, sizeof(t_env));
			new_node->key = ft_strdup(tmp[0]);
			new_node->value = ft_strdup(tmp[1]);
			new_node->prev = NULL;
			new_node->next = NULL;
			addback_env(&cmd->env_list, new_node);
		}
		ft_free_matrix(tmp);
	}
}
