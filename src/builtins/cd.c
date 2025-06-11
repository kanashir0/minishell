/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:32:07 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/11 15:08:52 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*get_env(t_env *env_list, char *key)
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

static int	pwd_oldpwd(t_env *env_list)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*cwd;

	pwd = get_env(env_list, "PWD");
	oldpwd = get_env(env_list, "OLDPWD");
	cwd = ft_collect_mem(1024, sizeof(char));
	if (!cwd)
		return (0);
	if (oldpwd)
	{
		untrack_pointer(oldpwd->value);
		oldpwd->value = ft_strdup(pwd->value);
	}
	getcwd(cwd, 1024);
	if (pwd)
	{
		untrack_pointer(pwd->value);
		pwd->value = ft_strdup(cwd);
	}
	untrack_pointer(cwd);
	return (0);
}

int	cd(char **args, t_command *cmd)
{
	int	path;
	int	flag;

	(void)flag;
	if (!args[1] || (args[1][0] == '~' && args[1][1] == '\0'))
		path = chdir(getenv("HOME"));
	else if ((args[1][0] == '-' && args[1][1] == '\0'))
		path = chdir(get_env(cmd->env_list, "OLDPWD")->value);
	else
		path = chdir(args[1]);
	if (!path)
		path = pwd_oldpwd(cmd->env_list);
	cmd->status = path != 0;
	return (path);
}
