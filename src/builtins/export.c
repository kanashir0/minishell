/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:38:54 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/21 16:20:21 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_key(char *str)
{
	if (!*str || !(ft_isalpha(*str) || *str == '_'))
		return (0);
	str++;
	while (*str && *str == '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);
		str++;
	}
	return (1);
}

static int	print_export_list(t_env *env_list)
{
	t_env	*node;

	node = env_list;
	while (node)
	{
		printf("declare -x %s", node->key);
		if (node->value)
			printf("=\"%s\"", node->value);
		printf("\n");
		node = node->next;
	}
	return (SUCCESS);
}

static t_env	*new_env(char *key, char *val)
{
	t_env	*node;

	node = ft_collect_mem(1, sizeof(t_env));
	node->key = ft_strdup(key);
	node->value = val;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

static void	export_arg(t_command *cmd, char *arg)
{
	t_env	*node;
	char	**kv;
	char	*key;
	char	*val;

	kv = ft_split(arg, '=');
	key = kv[0];
	if (kv[1])
		val = ft_strdup(kv[1]);
	else
		val = NULL;
	node = get_env(cmd->env_list, key);
	if (node)
	{
		untrack_pointer(node->value);
		node->value = val;
	}
	else
	{
		node = new_env(key, val);
		addback_env(&cmd->env_list, node);
	}
}

int	export(char **args, t_command *cmd)
{
	int	i;
	int	status;

	i = 1;
	status = SUCCESS;
	if (!args[i])
		return (print_export_list(cmd->env_list));
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			printf("export: `%s': not a valid identifier\n", args[i]);
			status = FAILURE;
		}
		else
			export_arg(cmd, args[i]);
		i++;
	}
	return (status);
}
