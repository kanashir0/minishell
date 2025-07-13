/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:07:18 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/13 14:09:41 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int execute_command(t_node *node, int input_fd, int output_fd)
{
	t_command	*cmd;
	char		**args;
	int			i;

	cmd  = get_cmd_context(NULL);
	args = node->argv;
	i = 0;
	while (args[i])
		i++;
	if (i > 0)
		update_under(cmd, args[i - 1]);
	else
		update_under(cmd, args[0]);
	cmd->status = is_builtin(args, cmd);
	if (cmd->status == -1)
		cmd->status = exec_path(args, input_fd, output_fd, cmd);

	return (cmd->status);
}

int	execute_redir(t_node *node, int input_fd, int output_fd)
{
	int			new_fd;
	pid_t		pid;
	t_command	*cmd;

	pid = fork();
	if (pid == 0)
	{
		new_fd = open_redir_file(node->redir_type, node->redir_file);
		if (new_fd < 0)
			exit (1);
		if (node->redir_type == REDIR_IN_TOKEN || node->redir_type == HEREDOC_TOKEN)
		{
			if (dup2(new_fd, STDIN_FILENO) == -1)
				error_handler("dup2 failed");
		}
		else if (node->redir_type == REDIR_OUT_TOKEN || node->redir_type == APPEND_TOKEN)
		{
			if (dup2(new_fd, STDOUT_FILENO) == -1)
				error_handler("dup2 failed");
		}
		close(new_fd);
		exit (execute_node(node->left, STDIN_FILENO, STDOUT_FILENO));
	}
	cmd = get_cmd_context(NULL);
	cmd->status = process_parent(input_fd, output_fd, cmd, pid);
	return (cmd->status);
}

int	execute_pipe(t_node *node, int input_fd, int output_fd)
{
	int			pipefd[2];
	pid_t		pid[2];
	int			status;

	pipe(pipefd);
	pid[0] = fork();
	if (pid[0] < 0)
		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), 1);
	process_signals(pid[0]);
	if (pid[0] == 0)
		pipe_child_left(node->left, pipefd, input_fd, pipefd[1]);
	pid[1] = fork();
	if (pid[1] < 0)
		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), 1);
	process_signals(pid[1]);
	if (pid[1] == 0)
		pipe_child_right(node->right, pipefd, pipefd[0], output_fd);
	close(pipefd[0]);
	close(pipefd[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	status = waitpid_status(pid);
	return (status);
}

int	execute_node(t_node *node, int input_fd, int output_fd)
{
	if (!node)
		return (1);
	if (node->type == PIPE_NODE)
		return (execute_pipe(node, input_fd, output_fd));
	else if (node->type == REDIR_NODE)
		return (execute_redir(node, input_fd, output_fd));
	else if (node->type == WORD_NODE)
		return (execute_command(node, input_fd, output_fd));
	else
		return (1);
}

int	execute_ast(t_node *root)
{
	t_command	*cmd;

	cmd = get_cmd_context(NULL);
	cmd->executing = 1;
	cmd->status = execute_node(root, STDIN_FILENO, STDOUT_FILENO);
	cmd->executing = 0;
	return (cmd->status);
}
