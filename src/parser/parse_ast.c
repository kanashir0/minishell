/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:31:16 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/09 12:23:34 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**consume_words(t_token **tokens)
{
	char	**argv;
	int		count;

	// supports up to 64 params/command
	argv = ft_collect_mem(1, sizeof(char *) * 64);
	count = 0;
	while (*tokens && (*tokens)->type == WORD_TOKEN)
	{
		argv[count++] = ft_strdup((*tokens)->value);
		consume_token(tokens);
	}
	argv[count] = '\0';
	if (count == 0)
		return (NULL);
	return (argv);
}

t_node	*parse_word(t_token **tokens)
{
	t_node			*word;
	t_node			*redir;
	t_token_type	redir_type;

	word = new_node(WORD_NODE, NULL, NULL);
	word->argv = consume_words(tokens);
	if (!word->argv)
	{
		untrack_pointer(word);
		return (NULL);
	}
	while (match_token(tokens, REDIR_OUT_TOKEN)
		|| match_token(tokens, REDIR_IN_TOKEN)
		|| match_token(tokens, HEREDOC_TOKEN)
		|| match_token(tokens, APPEND_TOKEN))
	{
		redir_type = consume_token(tokens)->type;
		if (!match_token(tokens, WORD_TOKEN))
		{
			free_ast(word);
			return (NULL);
		}
		redir = new_node(REDIR_NODE, word, NULL);
		redir->redir_file = ft_strdup((*tokens)->value);
		redir->redir_type = redir_type;
		word = redir;
		consume_token(tokens);
	}
	return (word);
}

t_node	*parse_pipe(t_token **tokens)
{
	t_node	*left;
	t_node	*right;
	t_node	*pipe;

	left = parse_word(tokens);
	if (!left)
		return (NULL);
	while (match_token(tokens, PIPE_TOKEN))
	{
		consume_token(tokens);
		right = parse_word(tokens);
		if (!right)
		{
			free_ast(left);
			return (NULL);
		}
		pipe = new_node(PIPE_NODE, left, right);
		left = pipe;
	}
	return (left);
}

t_node	*generate_ast(t_token **tokens)
{
	return (parse_pipe(tokens));
}
