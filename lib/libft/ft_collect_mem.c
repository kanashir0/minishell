/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collect_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:26:06 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/06/01 19:45:30 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	**get_mem_pointer(void)
{
	static t_list	*ptr;

	return (&ptr);
}

static void	track_pointer(void *content)
{
	if (!content)
		return ;
	ft_lstadd_front(get_mem_pointer(), ft_lstnew(content));
}

void	*ft_collect_mem(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		return (NULL);
	track_pointer(ptr);
	return (ptr);
}

void	untrack_pointer(void *content)
{
	t_list	**mem_list;
	t_list	*curr;
	t_list	*prev;

	if (!content)
		return ;
	mem_list = get_mem_pointer();
	curr = *mem_list;
	prev = NULL;
	while (curr)
	{
		if (curr->content == content)
		{
			if (prev)
				prev->next = curr->next;
			else
				*mem_list = curr->next;
			free(curr->content);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_clear_mem(void)
{
	ft_lstclear(get_mem_pointer(), &free);
}
