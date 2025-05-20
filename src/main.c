/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:25:24 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/05/20 19:03:46 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*read_line(void)
{
	char	*buf;

	buf = readline("minishell> ");
	return (buf);
}

char	**tokenizer(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	return (tokens);
}

void	execute(char **tokens)
{
	printf("%s\n", tokens[1]);
}

int	main(void)
{
	char	*line;
	char	**tokens;

	while (42)
	{
		line = read_line();
		if (!line)
			break ;
		tokens = tokenizer(line);
		execute(tokens);
	}
	return (0);
}
