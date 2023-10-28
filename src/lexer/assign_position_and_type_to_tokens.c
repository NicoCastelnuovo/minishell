/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_position_and_type_to_tokens.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:12:23 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/28 12:32:02 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_type_to_tkn(t_list *tkns_head)
{
	t_list			*temp;
	t_token_data	*tkn_data;

	temp = tkns_head;
	while (temp)
	{
		tkn_data = (t_token_data *)(temp->content);
		check_each_tkn_str(tkn_data);
		temp = temp->next;
	}
}

void	assign_quotation_to_tkn(t_list *tkns_head)
{
	t_list			*current_node;
	char			tkn_first_char;
	t_quotation		position;
	t_token_data	*tkn_data;

	position = NOT_QUOTED;
	current_node = tkns_head;
	while (current_node)
	{
		tkn_data = ((t_token_data *)(current_node->content));
		tkn_first_char = *(tkn_data->str);
		detect_quote(tkn_data, tkn_first_char, &position);
		tkn_data->quotation = position;
		if (tkn_data->quotation == IN_S_QUOTE && tkn_first_char == S_QUOTE)
			tkn_data->quotation = NOT_QUOTED;
		if (tkn_data->quotation == IN_D_QUOTE && tkn_first_char == D_QUOTE)
			tkn_data->quotation = NOT_QUOTED;
		current_node = current_node->next;
	}
}
