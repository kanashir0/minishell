/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:00:00 by gkana             #+#    #+#             */
/*   Updated: 2025/07/16 15:29:57 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_heredoc_filename(void)
{
	char	*filename;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_itoa(i);
	filename = ft_strjoin("heredoc_", tmp);
	untrack_pointer(tmp);
	while (access(filename, F_OK) == 0)
	{
		untrack_pointer(filename);
		i++;
		tmp = ft_itoa(i);
		filename = ft_strjoin("heredoc_", tmp);
		untrack_pointer(tmp);
	}
	return (filename);
}

static int	read_heredoc_input(int fd, const char *delimiter)
{
	char		*line;
	t_command	*cmd;

	cmd = get_cmd_context(NULL);
	cmd->status = 0;
	signal(SIGINT, heredoc_sigint_handler);
	while (42)
	{
		line = readline("> ");
		if (cmd->status == 130)
			return (free(line), 130);
		if (!line)
		{
			ft_printf_fd(STDOUT_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}

char	*handle_heredoc(const char *delimiter)
{
	char		*filename;
	int			status;
	int			fd;
	int			stdin_backup;

	filename = get_heredoc_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_cmd_error(filename, -2);
		return (untrack_pointer(filename), NULL);
	}
	stdin_backup = dup(STDIN_FILENO);
	status = read_heredoc_input(fd, delimiter);
	close(fd);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	signal(SIGINT, sigint_handler);
	if (status == 130)
	{
		get_cmd_context(NULL)->status = status;
		unlink(filename);
		return (untrack_pointer(filename), NULL);
	}
	return (filename);
}
