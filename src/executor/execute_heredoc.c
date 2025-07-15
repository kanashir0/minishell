/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:00:00 by gkana             #+#    #+#             */
/*   Updated: 2025/07/14 11:17:10 by cbrito-s         ###   ########.fr       */
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
		{
			free(line);
			return (130);
		}
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
	t_command	*cmd;
	int			status;
	int			fd;
	int			stdin_backup;

	cmd = get_cmd_context(NULL);
	filename = get_heredoc_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_cmd_error(filename, -2);
		untrack_pointer(filename);
		return (NULL);
	}
	stdin_backup = dup(STDIN_FILENO);
	status = read_heredoc_input(fd, delimiter);
	close(fd);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	signal(SIGINT, sigint_handler);
	if (status == 130)
	{
		cmd->status = status;
		unlink(filename);
		untrack_pointer(filename);
		return (NULL);
	}
	return (filename);
}
