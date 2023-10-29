/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_a_token_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:02:54 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/29 13:06:38 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_next_node(t_list *cur_node)
{
	t_list	*temp;

	temp = cur_node->next->next;
	ft_lstdelone(cur_node->next, free_token_data);
	cur_node->next = temp;
}
