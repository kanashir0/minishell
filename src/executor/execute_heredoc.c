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

static int	heredoc_child(char *filename, const char *delimiter)
{
	char	*line;
	int		fd;

	signal(SIGINT, heredoc_sigint_handler);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_cmd_error(filename, -2);
		exit(1);
	}
	while (42)
	{
		line = readline("> ");
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
	ft_clear_mem();
	close(fd);
	exit(0);
}

char	*handle_heredoc(const char *delimiter)
{
	char		*filename;
	pid_t		pid;
	t_command	*cmd;
	int			status;

	cmd = get_cmd_context(NULL);
	filename = get_heredoc_filename();
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		heredoc_child(filename, delimiter);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		cmd->status = WEXITSTATUS(status);
		unlink(filename);
		untrack_pointer(filename);
		return (NULL);
	}
	return (filename);
}
