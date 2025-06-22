/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:22:44 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/21 16:21:44 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
}
