/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_dollar_char_with_next_token.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:52:43 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/21 14:57:02 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_needed_to_merge(char first_char)
{
	bool	is_alpha;
	bool	is_digit;
	bool	is_under_score;

	is_alpha = ft_isalpha(first_char);
	is_digit = ft_isdigit(first_char);
	is_under_score = first_char == '_'; // norminette ??????
	if (!(is_alpha || is_digit || is_under_score || first_char == '?' || first_char == '\"' || first_char == '\'' )) // added || first_char == '?'
		return (false);
	else
		return (true);
}

void	merge_dollar_char_with_next_token(t_list *tkns_head)
{
	t_list		*cur_node;
	t_tkn_data	*cur_tkn_data;
	t_tkn_data	*next_tkn_data;

	cur_node = tkns_head;
	while (cur_node && cur_node->next)
	{
		cur_tkn_data = (t_tkn_data *)(cur_node->content);
		next_tkn_data = (t_tkn_data *)(cur_node->next->content);
		if ((cur_tkn_data->str)[0] == TKN_DOLLAR_CHAR)
		{
			if (!is_needed_to_merge(*(next_tkn_data->str)))
			{
				cur_node = cur_node->next;
				continue ;
			}
			// if (!is_needed_to_merge(*(next_tkn_data->str)))
			// 	return ;
			cur_tkn_data->str = join_two_strs(&(cur_tkn_data->str),
					next_tkn_data->str);
			remove_next_node(cur_node);
			cur_tkn_data->type = TKN_ENV_VAR;
			cur_tkn_data->str_len = ft_strlen(cur_tkn_data->str);
			((t_tkn_data *)(tkns_head->content))->list_size--;
		}
		cur_node = cur_node->next;
	}
}
