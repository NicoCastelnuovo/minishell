/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_following_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:34:06 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/29 20:09:20 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_following_space(t_list *tkns_head)
{
	t_list		*cur_node;
	t_tkn_data	*cur_tkn_data;
	t_tkn_data	*next_tkn_data;

	if (!tkns_head)
		return ;
	cur_node = tkns_head;
	while (cur_node && cur_node->next)
	{
		cur_tkn_data = (t_tkn_data *)(cur_node->content);
		next_tkn_data = (t_tkn_data *)(cur_node->next->content);
		if ((next_tkn_data->str)[0] == SPACE_CAHR
			|| (next_tkn_data->str)[0] == TAB_CHAR)
			cur_tkn_data->white_space = FOLLOWED_BY_WHITE_SPACE;
		else
			cur_tkn_data->white_space = NOT_FOLLOWED_BY_WHITE_SPACE;
		cur_node = cur_node->next;
	}
	if (!(cur_node->next))
		cur_tkn_data->white_space = NOT_FOLLOWED_BY_WHITE_SPACE;
}
