/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:38:54 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/05 19:29:14 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_key(char *str)
{
	if (!*str || !(ft_isalpha(*str) || *str == '_'))
		return (0);
	while (*str && *str != '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);
		str++;
	}
	return (1);
}

int	print_env(t_env **environ)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i]->key, "_", 1) == 0
				&& environ[i]->key[1] == '\0')
		{
			i++;
			continue ;
		}
		printf("declare -x %s", environ[i]->key);
		if (environ[i]->value)
			printf("=\"%s\"", environ[i]->value);
		printf("\n");
		i++;
	}
	return (SUCCESS);
}

static int	print_export_list(t_env *env_list)
{
	t_env	**environ;
	int		count;
	int		i;

	environ = env_list_copy(env_list);
	count = count_env_arr(environ);
	environ = env_list_ord(environ, count);
	i = print_env(environ);
	return (i);
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
			printf("minishell: export: `%s': not a valid identifier\n", args[i]);
			status = FAILURE;
		}
		else
		{
			if (args[i][0] == '_' && args[i][1] == '\0')
				break ;
			export_arg(cmd, args[i]);
		}
		i++;
	}
	return (status);
}
