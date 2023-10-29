/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_dollar_char_with_next_token.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:52:43 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/29 17:37:52 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_needed_to_merge(char first_char)
{
	if (!((ft_isalpha(first_char)) || ft_isdigit(first_char) || (first_char == '_')))
		return (false);
	else
		return (true);
}

void	merge_dollar_char_with_next_token(t_list *tkns_head)
{
	t_list			*cur_node;
	t_token_data	*cur_tkn_data;
	t_token_data	*next_tkn_data;

	cur_node = tkns_head;
	while (cur_node && cur_node->next)
	{
		cur_tkn_data = (t_token_data *)(cur_node->content);
		next_tkn_data = (t_token_data *)(cur_node->next->content);
		if ((cur_tkn_data->str)[0] == DOLLAR_CHAR)
		{
			if (!is_needed_to_merge(*(next_tkn_data->str)))
				return ;
			cur_tkn_data->str = join_two_strs(&(cur_tkn_data->str), next_tkn_data->str);
			remove_next_node(cur_node);
			cur_tkn_data->type = ENV_VAR;
			cur_tkn_data->str_len = ft_strlen(cur_tkn_data->str);
			((t_token_data *)(tkns_head->content))->list_size--;
		}
		cur_node = cur_node->next;
	}
}
