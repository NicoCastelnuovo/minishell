/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:30:47 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/27 19:01:40 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_prev_node(t_list *tkns_head)
{
	t_token_data	*next_tkn_data;
	t_list			*temp;

	temp = tkns_head;
	while (temp)
	{
		if (((t_token_data *)(tkns_head->content))->list_size == 1)
			return (NULL);
		next_tkn_data = (t_token_data *)(temp->next->content);
		if (*(next_tkn_data->str) == SPACE_CAHR
			|| *(next_tkn_data->str) == TAB_CHAR)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	delete_spaces(t_list **tkns_head)
{
	t_list			*temp;
	t_list			*before_white_space;
	t_token_data	*cur_tkn_data;

	int i = 0;
	temp = *tkns_head;
	while (temp)
	{
		cur_tkn_data = (t_token_data *)(temp->content);
		if (*(cur_tkn_data->str) == SPACE_CAHR
			|| *(cur_tkn_data->str) == TAB_CHAR)
		{
			before_white_space = get_prev_node(*tkns_head);
			if (((t_token_data *)((*tkns_head)->content))->list_size == 1)
			{
				ft_lstdelone(temp, free_tkn_str);
				*tkns_head = NULL;
				return ;
			}
			before_white_space->next = temp->next;
			ft_lstdelone(temp, free_tkn_str);
			((t_token_data *)((*tkns_head)->content))->list_size--;
		}
			
		i++;
		temp = temp->next;
	}
}