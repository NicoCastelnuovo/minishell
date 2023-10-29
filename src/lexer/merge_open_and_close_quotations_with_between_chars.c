/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_open_and_close_quotations_with_betwee        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:03:49 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/29 14:45:33 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_two_str_node(t_list *tkns_head, t_list *cur_node, t_list *cur_quoted_node, char tkn_type)
{
	t_token_data	*temp2_tkn_data;
	t_token_data	*temp1_tkn_data;

	temp1_tkn_data = (t_token_data *)(cur_node->content);
	temp2_tkn_data = (t_token_data *)(cur_quoted_node->content);
	if (tkn_type == S_QUOTE && temp2_tkn_data->quote_status != CLOSED_QUOTE)
	{
		(temp1_tkn_data)->type = NOT_CLOSED_S_QUOTE_STR;
		(temp1_tkn_data)->quotation = IN_S_QUOTE;
	}
	else if (tkn_type == D_QUOTE && temp2_tkn_data->quote_status !=CLOSED_QUOTE)
	{
		(temp1_tkn_data)->type = NOT_CLOSED_D_QUOTE_STR;
		(temp1_tkn_data)->quotation = IN_D_QUOTE;
	}
	join_two_strs(&temp1_tkn_data->str, temp2_tkn_data->str);
	remove_next_node(cur_node);
	((t_token_data *)(tkns_head->content))->list_size--;
	(temp1_tkn_data)->str_len = ft_strlen((temp1_tkn_data)->str);
}

void	merge_closing_quote(t_list *tkns_head, t_list *cur_node, t_list *cur_quoted_node, char tkn_type)
{
	if (!cur_node->next)
		return ;
	if ((((t_token_data *)(cur_node->next->content))->str)[0] == tkn_type 
		&& (((t_token_data *)(cur_node->next->content))->quote_status) == CLOSED_QUOTE)
	{
		cur_quoted_node = cur_node->next;
		merge_two_str_node(tkns_head, cur_node, cur_quoted_node, tkn_type);
	}
}

bool	is_closing_quote_pair(t_token_data *temp1_tkn_data, t_list *temp2, char tkn_type)
{
	t_token_data	*temp2_tkn_data;

	if (!temp2)
		return (false);
	temp2_tkn_data = (t_token_data *)(temp2->content);
	if (((temp2_tkn_data->str)[0] == tkn_type
		&& (temp2_tkn_data)->quote_status == CLOSED_QUOTE))
	{
		(temp1_tkn_data)->quote_status = OPEN_AND_CLOSED_PAIRS;
		if (tkn_type == S_QUOTE)
		{
			(temp1_tkn_data)->type = S_QUOTED_STR;
			(temp1_tkn_data)->quotation = IN_S_QUOTE;
		}
		else if (tkn_type == D_QUOTE)
		{
			(temp1_tkn_data)->type = D_QUOTED_STR;
			(temp1_tkn_data)->quotation = IN_D_QUOTE;
		}
		return (true);
	}
	return (false);
}

bool	is_closing_quote_found(t_list *tkns_head, t_list *cur_node, t_list **cur_quoted_node, char tkn_type)
{
	t_list			*temp;
	t_token_data	*cur_tkn_data;

	cur_tkn_data = (t_token_data *)(cur_node->content);
	temp = (*cur_quoted_node)->next;
	if (((t_token_data *)((*cur_quoted_node)->content))->quote_status != CLOSED_QUOTE)
	{
		merge_two_str_node(tkns_head, cur_node, *cur_quoted_node, tkn_type);
		*cur_quoted_node = temp;
	}
	if (is_closing_quote_pair(cur_tkn_data, *cur_quoted_node, tkn_type))
		return (true);
	return (false);
}

void	merge_quotations(t_list *tkns_head)
{
	t_list			*cur_node;
	t_list			*cur_quoted_node;
	t_token_data	*cur_tkn_data;
	char			tkn_type;

	cur_node = tkns_head;
	cur_quoted_node = tkns_head;
	while (cur_node)
	{
		cur_tkn_data = (t_token_data *)(cur_node->content);
		if ((*(cur_tkn_data->str) == S_QUOTE || (cur_tkn_data->str)[0] == D_QUOTE)
			&& cur_tkn_data->quote_status == OPEN_QUOTE)
		{
			cur_quoted_node = cur_node->next;
			tkn_type = *(cur_tkn_data->str);
			while (cur_quoted_node)
			{
				if (is_closing_quote_found(tkns_head, cur_node, &cur_quoted_node, tkn_type))
					break ;
			}
			merge_closing_quote(tkns_head, cur_node, cur_quoted_node, tkn_type);
		}
		cur_node = cur_node->next;
	}
}
