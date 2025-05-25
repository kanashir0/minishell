/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:31:00 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/05/25 14:43:54 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	n_flag(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i] && args[i][j] == '-' && args[i][++j] == 'n')
	{
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		i++;
		j = 0;
	}
	return (i);
}

int	echo(char **args)
{
	int	i;
	int	newline;

	i = n_flag(args);
	newline = 1;
	if (i > 1)
		newline = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
