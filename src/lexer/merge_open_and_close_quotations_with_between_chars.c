/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_open_and_close_quotations_with_betwee        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:03:49 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/28 20:38:36 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_two_str_node(t_list *tkns_head, t_list *temp1, t_list *temp2, t_token_data *temp1_tkn_data, char tkn_type)
{
	t_token_data	*temp2_tkn_data;
	t_list			*temp3;
	char			*str_temp;

	temp2_tkn_data = (t_token_data *)(temp2->content);
	str_temp = temp1_tkn_data->str;
	temp1_tkn_data->str = ft_strjoin(temp1_tkn_data->str, temp2_tkn_data->str);
	free(str_temp);
	temp3 = temp2->next;
	temp1->next = temp3;
	ft_lstdelone(temp2, free_token_data);
	((t_token_data *)(tkns_head->content))->list_size--;
	(temp1_tkn_data)->str_len = ft_strlen((temp1_tkn_data)->str);
	(temp1_tkn_data)->quote_status = OPEN_AND_CLOSE_PAIRS;
	if (tkn_type == S_QUOTE)
		(temp1_tkn_data)->type = S_QUOTED_STR;
	else if (tkn_type == D_QUOTE)
		(temp1_tkn_data)->type = D_QUOTED_STR;
}

void	merge_closing_quote(t_list *tkns_head, t_list *temp1, t_list *temp2, char tkn_type)
{
	t_token_data	*temp1_tkn_data;

	if (!temp1->next)
		return ;
	temp1_tkn_data = (t_token_data *)(temp1->content);
	if ((((t_token_data *)(temp1->next->content))->str)[0] == tkn_type 
		&& (((t_token_data *)(temp1->next->content))->quote_status) == CLOSED_QUOTE)
	{
		temp2 = temp1->next;
		merge_two_str_node(tkns_head, temp1, temp2, temp1_tkn_data, tkn_type);
	}
}

bool	is_closing_quote_pair(t_list *temp2, char tkn_type)
{
	t_token_data	*temp2_tkn_data;

	if (!temp2)
		return (false);
	temp2_tkn_data = (t_token_data *)(temp2->content);
	if (((temp2_tkn_data->str)[0] == tkn_type
		&& (temp2_tkn_data)->quote_status == CLOSED_QUOTE))
		return (true);
	return (false);
}

void	merge_quotations(t_list *tkns_head)
{
	t_list			*temp1;
	t_list			*temp2;
	t_list			*temp3;
	t_token_data	*temp1_tkn_data;
	char			tkn_type;

	temp1 = tkns_head;
	temp2 = tkns_head;
	// tkn_type = 0;
	while (temp1)
	{
		temp1_tkn_data = (t_token_data *)(temp1->content);
		if ((*(temp1_tkn_data->str) == S_QUOTE || (temp1_tkn_data->str)[0] == D_QUOTE)
			&& temp1_tkn_data->quote_status == OPEN_QUOTE)
		{
			temp2 = temp1->next;
			tkn_type = *(temp1_tkn_data->str);
			while (temp2)
			{
				temp3 = temp2->next;
				merge_two_str_node(tkns_head, temp1, temp2, temp1_tkn_data, tkn_type);
				temp2 = temp3;
				// if (!temp2)
				// 	break ;
				if (is_closing_quote_pair(temp2, tkn_type))
					break ;
			}
			merge_closing_quote(tkns_head, temp1, temp2, tkn_type);
		}
		// if (!temp2)
		// 	return;
		// merge_closing_quote(tkns_head, temp1, temp2, tkn_type);
		temp1 = temp1->next;
	}
}
//Hello '\"\"\" some tokens 	' continue after quotation is closed