/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:30:47 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/28 19:40:33 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_prev_node(t_list *tkns_head)
{
	t_token_data	*next_tkn_data;
	t_list			*temp;

	temp = tkns_head;
	while (temp && temp->next)
	{
		// if (((t_token_data *)(tkns_head->content))->list_size == 1)
		// 	return (NULL);
		next_tkn_data = (t_token_data *)(temp->next->content);
		if ((*(next_tkn_data->str) == SPACE_CAHR
			|| *(next_tkn_data->str) == TAB_CHAR)
			&& next_tkn_data->quotation == NOT_QUOTED)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	del_space_node_as_first_tkn(t_list **tkns_head)
{
	t_list			*temp;
	t_token_data	*tkns_head_data;
	int				list_size;

	temp = *tkns_head;
	while (temp)
	{
		tkns_head_data = (t_token_data *)((*tkns_head)->content);
		if (((tkns_head_data->str)[0] == SPACE_CAHR
			|| *(tkns_head_data->str) == TAB_CHAR)
			&& tkns_head_data->quotation == NOT_QUOTED)
		{
			list_size = ((t_token_data *)((*tkns_head)->content))->list_size - 1;
			*tkns_head = (*tkns_head)->next;
			ft_lstdelone(temp, free_token_data);
			temp = *tkns_head;
			if (*tkns_head)
				((t_token_data *)((*tkns_head)->content))->list_size = list_size;
			continue ;
		}
		else
			return ;
		temp = temp->next;
	}
}

void	del_space_node_in_middle_or_end(t_list *tkns_head)
{
	t_list			*temp;
	t_list			*temp2;
	t_list			*before_white_space;
	t_token_data	*cur_tkn_data;
	
	temp = tkns_head;
	while (temp)
	{
		cur_tkn_data = (t_token_data *)(temp->content);
		if ((*(cur_tkn_data->str) == SPACE_CAHR
			|| *(cur_tkn_data->str) == TAB_CHAR)
			&& cur_tkn_data->quotation == NOT_QUOTED)
		{
			before_white_space = get_prev_node(tkns_head);
			// if (((t_token_data *)((tkns_head)->content))->list_size == 1)
			// {
			// 	ft_lstdelone(temp, free_tkn_str);
			// 	tkns_head = NULL;
			// 	return ;
			// }
			before_white_space->next = temp->next;
			temp2 = temp->next;
			ft_lstdelone(temp, free_token_data);
			((t_token_data *)((tkns_head)->content))->list_size--;
			temp = temp2;
			continue ;
		}
		temp = temp->next;
	}
}

void	delete_spaces(t_list **tkns_head)
{
	// t_list			*temp;
	// t_list			*before_white_space;
	// t_token_data	*cur_tkn_data;
	
	del_space_node_as_first_tkn(tkns_head);
	del_space_node_in_middle_or_end(*tkns_head);
	
}