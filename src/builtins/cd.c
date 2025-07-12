/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:32:07 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/07/12 14:27:08 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_flag(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && ft_isalpha(args[i][1]))
			return (i);
		i++;
	}
	return (0);
}

static int	pwd_oldpwd(t_env *env_list)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*cwd;

	pwd = get_env(env_list, "PWD");
	oldpwd = get_env(env_list, "OLDPWD");
	if (!pwd || !oldpwd)
		error_handler("Error: Could not find environment variables\n");
	cwd = ft_collect_mem(1024, sizeof(char));
	if (!cwd)
		error_handler("Error: When using malloc\n");
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
	int	status;
	int	flag;

	flag = find_flag(args);
	if (flag && !(args[1][0] != '-'))
		return (printf("minishell: cd: %s: invalid option\n", args[flag]), 2);
	if (!args[1] || (args[1][0] == '~' && args[1][1] == '\0'))
		status = chdir(get_env(cmd->env_list, "HOME")->value);
	else if ((args[1][0] == '-' && args[1][1] == '\0'))
		status = chdir(get_env(cmd->env_list, "OLDPWD")->value);
	else if (args[2] && ft_strlen(args[2]) > 0)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	else
		status = chdir(args[1]);
	if (!status)
		status = pwd_oldpwd(cmd->env_list);
	else
		return (printf("minishell: cd: %s: No such file or directory\n", args[1]), 1);
	return (status);
}
