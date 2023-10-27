/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_two_less_or_greater_than.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:46:14 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/27 19:17:22 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tkn_str(void *content)
{
	t_token_data	*tkn_data;
	tkn_data = (t_token_data *)content;
	free(tkn_data->str);
	tkn_data->str = NULL;
}

static void	merge_less_or_greater_than(t_list *tkns_head, t_list *node, char redirect)
{
	t_token_data	*tkn_data;
	t_list			*temp;

	free(((t_token_data *)(node->content))->str);
	((t_token_data *)(node->content))->str = malloc( 3 * sizeof(char));
	tkn_data = (t_token_data *)node->content;
	tkn_data->str[2] = '\0';
	ft_memset(tkn_data->str, redirect, 2);
	if (redirect == REDIRECT_IN)
		tkn_data->type = HERE_DOC;
	else if (redirect == REDIRECT_OUT)
		tkn_data->type = REDIRECT_OUT_CONCAT;
	tkn_data->str_len++;
	temp = node->next;
	node->next = node->next->next;
	ft_lstdelone(temp, free_tkn_str);
	((t_token_data *)(tkns_head->content))->list_size--;
}

void	find_consecutive_less_or_greater_than(t_list *tkns_head)
{
	t_list			*temp;
	t_token_data	*cur_tkn_data;
	t_token_data	*next_tkn_data;
	char			tkn_first_char;
	
	temp = tkns_head;
	while (temp && temp->next)
	{
		cur_tkn_data = (t_token_data *)(temp->content);
		next_tkn_data = (t_token_data *)(temp->next->content);
		tkn_first_char = cur_tkn_data->str[0];
		if ((cur_tkn_data->str_len == 1 && next_tkn_data->str_len == 1)
			&& (((cur_tkn_data->str)[0] == REDIRECT_OUT && (next_tkn_data->str)[0] == REDIRECT_OUT)
			|| ((cur_tkn_data->str)[0] == REDIRECT_IN && (next_tkn_data->str)[0] == REDIRECT_IN)))
			merge_less_or_greater_than(tkns_head, temp, tkn_first_char);
		temp = temp->next;
	}
}