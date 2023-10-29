/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_two_less_or_greater_than.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:46:14 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/29 16:32:31 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	merge_tokens(t_list *tkns_head, t_list *cur_node, char redirect)
{
	t_token_data	*cur_tkn_data;
	t_token_data	*next_tkn_data;

	cur_tkn_data = (t_token_data *)cur_node->content;
	next_tkn_data = (t_token_data *)cur_node->next->content;
	join_two_strs(&(cur_tkn_data->str), next_tkn_data->str);
	remove_next_node(cur_node);
	if (redirect == REDIRECT_IN)
		cur_tkn_data->type = HERE_DOC;
	else if (redirect == REDIRECT_OUT)
		cur_tkn_data->type = REDIRECT_OUT_CONCAT;
	cur_tkn_data->str_len++;
	((t_token_data *)(tkns_head->content))->list_size--;
}

void	merge_consecutive_less_or_greater_than(t_list *tkns_head)
{
	t_list			*cur_node;
	t_token_data	*cur_tkn_data;
	t_token_data	*next_tkn_data;
	char			tkn_first_char;

	cur_node = tkns_head;
	while (cur_node && cur_node->next)
	{
		cur_tkn_data = (t_token_data *)(cur_node->content);
		next_tkn_data = (t_token_data *)(cur_node->next->content);
		tkn_first_char = cur_tkn_data->str[0];
		if ((cur_tkn_data->str_len == 1 && next_tkn_data->str_len == 1)
			&& (((cur_tkn_data->str)[0] == REDIRECT_OUT
				&& (next_tkn_data->str)[0] == REDIRECT_OUT)
			|| ((cur_tkn_data->str)[0] == REDIRECT_IN
			&& (next_tkn_data->str)[0] == REDIRECT_IN)))
			merge_tokens(tkns_head, cur_node, tkn_first_char);
		cur_node = cur_node->next;
	}
}
