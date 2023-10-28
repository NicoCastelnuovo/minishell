/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_dollar_char_with_next_token.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:52:43 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/28 19:55:55 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_dollar_char_with_next_token(t_list *tkns_head)
{
	t_list			*temp_node;
	t_list			*temp_node2;
	t_token_data	*cur_tkn_data;
	t_token_data	*next_tkn_data;
	char			*temp_str;

	temp_node = tkns_head;
	while (temp_node && temp_node->next)
	{
		cur_tkn_data = (t_token_data *)(temp_node->content);
		next_tkn_data = (t_token_data *)(temp_node->next->content);
		if ((cur_tkn_data->str)[0] == DOLLAR_CHAR)
		{
			temp_str = cur_tkn_data->str;
			cur_tkn_data->str = ft_strjoin(cur_tkn_data->str, next_tkn_data->str); //next_tkn_data->str == NULL?
			free(temp_str);
			temp_node2 = temp_node->next->next;
			ft_lstdelone(temp_node->next, free_token_data);
			temp_node->next = temp_node2;
			cur_tkn_data->type = ENV_VAR;
			cur_tkn_data->str_len = ft_strlen(cur_tkn_data->str);
			((t_token_data *)(tkns_head->content))->list_size--;
		}
		temp_node = temp_node->next;
	}
}
