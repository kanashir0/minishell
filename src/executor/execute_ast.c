/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:07:18 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/15 21:07:27 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int execute_command(t_node *node)
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
	{
		update_under(cmd, args[i - 1]);
		cmd->status = is_builtin(args, cmd);
		if (cmd->status == -1)
			cmd->status = exec_path(args, cmd);
	}
	else
		cmd->status = 0;
	return (cmd->status);
}

int	execute_redir(t_node *node)
{
	int		new_fd;
	int		input_fd;
	int		output_fd;
	int		status;

	input_fd = dup(STDIN_FILENO);
	output_fd = dup(STDOUT_FILENO);
	new_fd = open_redir_file(node->redir_type, node->redir_file);
	if (new_fd < 0)
	{
		close(input_fd);
		close(output_fd);
		return (1);
	}
	if (node->redir_type == REDIR_IN_TOKEN || node->redir_type == HEREDOC_TOKEN)
		dup2(new_fd, STDIN_FILENO);
	else if (node->redir_type == REDIR_OUT_TOKEN || node->redir_type == APPEND_TOKEN)
		dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	status = execute_node(node->left);
	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(input_fd);
	close(output_fd);
	return (status);
}

int	execute_pipe(t_node *node)
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
		pipe_child_left(node->left, pipefd);
	pid[1] = fork();
	if (pid[1] < 0)
		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), 1);
	process_signals(pid[1]);
	if (pid[1] == 0)
		pipe_child_right(node->right, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	status = waitpid_status(pid);
	setup_signals();
	return (status);
}

int	execute_node(t_node *node)
{
	if (!node)
		return (1);
	if (node->type == PIPE_NODE)
		return (execute_pipe(node));
	else if (node->type == REDIR_NODE)
		return (execute_redir(node));
	else if (node->type == WORD_NODE)
		return (execute_command(node));
	else
		return (1);
}

int	execute_ast(t_node *root)
{
	t_command	*cmd;

	cmd = get_cmd_context(NULL);
	cmd->executing = 1;
	cmd->status = execute_node(root);
	cmd->executing = 0;
	return (cmd->status);
}
