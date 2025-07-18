/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:46:33 by gkana             #+#    #+#             */
/*   Updated: 2025/07/16 17:11:04 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_heredoc_file(t_command *cmd, char *filename)
{
	int		i;
	char	**new_files;

	i = 0;
	while (cmd->heredoc_files && cmd->heredoc_files[i])
		i++;
	new_files = ft_collect_mem(i + 2, sizeof(char *));
	i = 0;
	while (cmd->heredoc_files && cmd->heredoc_files[i])
	{
		new_files[i] = cmd->heredoc_files[i];
		i++;
	}
	new_files[i] = ft_strdup(filename);
	new_files[i + 1] = NULL;
	if (cmd->heredoc_files)
		untrack_pointer(cmd->heredoc_files);
	cmd->heredoc_files = new_files;
}

void	cleanup_heredocs(t_command *cmd)
{
	int	i;

	if (!cmd->heredoc_files)
		return ;
	i = 0;
	while (cmd->heredoc_files[i])
	{
		unlink(cmd->heredoc_files[i]);
		untrack_pointer(cmd->heredoc_files[i]);
		i++;
	}
	untrack_pointer(cmd->heredoc_files);
	cmd->heredoc_files = NULL;
}
