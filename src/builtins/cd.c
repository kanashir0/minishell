/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:32:07 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/05/30 17:49:51 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(char **args, t_command *cmd)
{
	int	path_cd;
	int	flag;

	(void)flag;
	(void)cmd;
	if (!args[1] || ft_strncmp(args[1], "~", 1))
		path_cd = chdir(getenv("HOME"));
	return (path_cd);
}
