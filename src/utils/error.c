/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:58:40 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/01 18:02:33 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_handler(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_clear_mem();
	exit(EXIT_FAILURE);
}