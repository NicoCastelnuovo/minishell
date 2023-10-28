/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_open_and_close_quotations_with_betwee        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:03:49 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/28 16:32:37 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_two_str_node(t_list *tkns_head, t_list *temp1, t_list *temp2, t_token_data *temp1_tkn_data)
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
	ft_lstdelone(temp2, free_tkn_str);
	((t_token_data *)(tkns_head->content))->list_size--;
	((t_token_data *)(tkns_head->content))->str_len = ft_strlen(((t_token_data *)(tkns_head->content))->str);
}

void	merge_quotations(t_list *tkns_head)
{
	t_list			*temp1;
	t_list			*temp2;
	t_list			*temp3;
	t_token_data	*temp1_tkn_data;
	t_token_data	*temp2_tkn_data;
	char			token_type;
	// char			*str_temp;

	temp1 = tkns_head;
	temp2 = tkns_head;
	while (temp1)
	{
		temp1_tkn_data = (t_token_data *)(temp1->content);
		if ((*(temp1_tkn_data->str) == S_QUOTE || (temp1_tkn_data->str)[0] == D_QUOTE)
			&& temp1_tkn_data->quote_status == OPEN_QUOTE)
		{
			temp2 = temp1->next;
			token_type = *(temp1_tkn_data->str);
			while (temp2)
			{
				// temp2_tkn_data = (t_token_data *)(temp2->content);
				// str_temp = temp1_tkn_data->str;
				// temp1_tkn_data->str = ft_strjoin(temp1_tkn_data->str, temp2_tkn_data->str);
				// free(str_temp);
				// temp3 = temp2->next;
				// temp1->next = temp3;
				// ft_lstdelone(temp2, free_tkn_str);
				merge_two_str_node(tkns_head, temp1, temp2, temp1_tkn_data);
				temp3 = temp2->next;
				temp2 = temp3;
				if (!temp2)
					break ;
				temp2_tkn_data = (t_token_data *)(temp2->content);
				if (((temp2_tkn_data->str)[0] == token_type
					&& (temp2_tkn_data)->quote_status == CLOSED_QUOTE))
					break ;
			}
		}
		if (!temp2)
			return;
		if ((((t_token_data *)(temp1->next->content))->str)[0] == token_type 
			&& (((t_token_data *)(temp1->next->content))->quote_status) == CLOSED_QUOTE)
		{
			temp2 = temp1->next;
			// temp2_tkn_data = (t_token_data *)(temp2->content);
			// str_temp = temp1_tkn_data->str;
			// temp1_tkn_data->str = ft_strjoin(temp1_tkn_data->str, temp2_tkn_data->str);
			// free(str_temp);
			// temp3 = temp2->next;
			// temp1->next = temp3;
			// ft_lstdelone(temp2, free_tkn_str);
			merge_two_str_node(tkns_head, temp1, temp2, temp1_tkn_data);
		}
		temp1 = temp1->next;
	}
}
//Hello '\"\"\" some tokens 	' continue after quotation is closed