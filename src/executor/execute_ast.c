/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:07:18 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/01 20:29:47 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_command(t_node *node, int input_fd, int output_fd)
{
	t_command	*cmd;

	cmd = get_cmd_context(NULL);
	cmd->status = is_builtin(node->argv, cmd);
	if (cmd->status == -1)
		cmd->status = exec_path(node->argv, input_fd, output_fd, cmd);
	return (cmd->status);
}

int	execute_redir(t_node *node, int input_fd, int output_fd)
{
	int	new_fd;

	new_fd = open_redir_file(node->redir_type, node->redir_file);
	if (new_fd < 0)
		return (1);
	if (node->redir_type == REDIR_IN_TOKEN || node->redir_type == HEREDOC_TOKEN)
		return (execute_node(node->left, new_fd, output_fd));
	else if (node->redir_type == REDIR_OUT_TOKEN || node->redir_type == APPEND_TOKEN)
		return (execute_node(node->left, input_fd, new_fd));
	return (1);
}

int	execute_pipe(t_node *node, int input_fd, int output_fd)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	pipe(pipefd);
	left_pid = fork();
	if (left_pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execute_node(node->left, input_fd, pipefd[1]);
		close(pipefd[1]);
		exit(0);
	}
	right_pid = fork();
	if (right_pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		execute_node(node->right, pipefd[0], output_fd);
		close(pipefd[0]);
		exit(0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, NULL, 0);
	return (0);
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
	return (execute_node(root, STDIN_FILENO, STDOUT_FILENO));
}
