/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:07:18 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/29 17:36:52 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_command(t_node *node, int input_fd, int output_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		execvp(node->argv[0], node->argv); // TODO refatorar funçao execute
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (output_fd != STDOUT_FILENO)
		close(output_fd);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
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
		execute_node(node->left, input_fd, pipefd[1]);
		exit(0);
	}
	right_pid = fork();
	if (right_pid == 0)
	{
		close(pipefd[1]);
		execute_node(node->right, pipefd[0], output_fd);
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