/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:38:54 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/21 18:52:43 by cbrito-s         ###   ########.fr       */
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

t_env	**env_list_copy(t_env *env_list)
{
	t_env	**env_ord;
	int		i;
	int		len_env;

	len_env = count_env(env_list);
	env_ord = ft_collect_mem(sizeof(t_env *), len_env + 1);
	if (!env_ord)
		perror("malloc");
	i = 0;
	while (env_list)
	{
		env_ord[i++] = env_list;
		env_list = env_list->next;
	}
	env_ord[i] = NULL;
	return (env_ord);
}

t_env	**env_list_ord(t_env **environ, int count)
{
	int		swap;
	int		i;
	int		len;
	t_env	*tmp;

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
				tmp = environ[i];
				environ[i] = environ[i + 1];
				environ[i + 1] = tmp;
				swap = 1;
			}
			i++;
		}
		if (swap == 0)
			break ;
	}
	return (environ);
}

int	print_env(t_env **environ)
{
	int	i;

	i = 0;
	while (environ[i])
	{
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

static void export_arg(t_command *cmd, char *arg)
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
