/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_following_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:34:06 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/03 09:57:06 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_following_space_status(t_list *tkns_head)
{
	t_list		*cur_node;
	t_tkn_data	*cur_tkn_data;
	t_tkn_data	*next_tkn_data;

	if (!tkns_head)
		return ;
	cur_node = tkns_head;
	cur_tkn_data = (t_tkn_data *)(cur_node->content);
	while (cur_node && cur_node->next)
	{
		cur_tkn_data = (t_tkn_data *)(cur_node->content);
		next_tkn_data = (t_tkn_data *)(cur_node->next->content);
		if ((next_tkn_data->str)[0] == TKN_SPACE_CAHR
			|| (next_tkn_data->str)[0] == TKN_TAB_CHAR)
			cur_tkn_data->white_space = FOLLOWED_BY_WHITE_SPACE;
		else
			cur_tkn_data->white_space = NOT_FOLLOWED_BY_WHITE_SPACE;
		cur_node = cur_node->next;
	}
	cur_tkn_data = (t_tkn_data *)(cur_node->content);
	if (!(cur_node->next) && cur_tkn_data->white_space == UNKNOWN_WHITE_SPACE)
		cur_tkn_data->white_space = NOT_FOLLOWED_BY_WHITE_SPACE;
}
