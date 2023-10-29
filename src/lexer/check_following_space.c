/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_following_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:34:06 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/29 10:51:33 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_following_space(t_list *tkns_head)
{
	t_list			*temp;
	t_token_data	*next_tkn_data;

	if (!tkns_head)
		return ;
	temp = tkns_head;
	while (temp && temp->next)
	{
		next_tkn_data = (t_token_data *)(temp->next->content);
		if ((next_tkn_data->str)[0] == SPACE_CAHR || (next_tkn_data->str)[0] == TAB_CHAR)
			((t_token_data *)(temp->content))->white_space = FOLLOWED_BY_WHITE_SPACE;
		else
			((t_token_data *)(temp->content))->white_space = NOT_FOLLOWED_BY_WHITE_SPACE;
		temp = temp->next;
	}
	if (!(temp->next))
		((t_token_data *)(temp->content))->white_space = NOT_FOLLOWED_BY_WHITE_SPACE;
}
