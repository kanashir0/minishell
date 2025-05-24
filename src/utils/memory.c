/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:57:12 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/05/24 12:54:22 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	if (size <= 0)
		return (malloc(0));
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, size);
	return (ptr);
}

void	free_command(t_command *cmd)
{
	size_t	args_size;

	args_size = 0;
	free(cmd->input);
	while (cmd->args[args_size])
		free(cmd->args[args_size++]);
	free(cmd->args);
	free(cmd);
}