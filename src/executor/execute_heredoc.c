/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:00:00 by gkana             #+#    #+#             */
/*   Updated: 2025/07/17 22:24:00 by gyasuhir         ###   ########.fr       */
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

static int	check_heredoc_conditions(const char *line,
	char *raw_delimiter)
{
	if (get_cmd_context(NULL)->status == 130)
		return (130);
	if (!line)
	{
		ft_printf_fd(STDOUT_FILENO, "minishell: "WARNING" (wanted `%s')\n",
			raw_delimiter);
		return (1);
	}
	if (ft_strncmp(line, raw_delimiter, ft_strlen(raw_delimiter) + 1) == 0)
		return (1);
	return (0);
}

static void	write_and_free_line(int fd, char *line, char *raw_delimiter)
{
	if (should_expand(raw_delimiter) == 1)
	{
		unquoted_heredoc(&line);
		ft_putendl_fd(line, fd);
	}
	else
	{
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static int	read_heredoc_input(int fd, const char *delimiter)
{
	char	*raw;
	char	*line;
	int		status;

	raw = strip_quotes((char *)(delimiter));
	get_cmd_context(NULL)->status = 0;
	signal(SIGINT, heredoc_sigint_handler);
	while (42)
	{
		line = readline("> ");
		status = check_heredoc_conditions(line, raw);
		if (status == 130)
		{
			free(line);
			return (130);
		}
		if (status == 1)
		{
			free(line);
			break ;
		}
		write_and_free_line(fd, line, raw);
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
