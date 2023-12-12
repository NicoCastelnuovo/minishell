/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:35:23 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/10 18:27:17 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_word_or_string(t_tkn_type type)
{
	if (type == TKN_WORD || type == TKN_S_QUOTED_STR
		|| type == TKN_D_QUOTED_STR || type == TKN_ENV_VAR)
		return (1);
	return (0);
}

// 			cur_tkn_data->str = join_two_strs(&(cur_tkn_data->str),
// 					next_tkn_data->str);
// 			remove_next_node(cur_node);
// 			cur_tkn_data->type = TKN_ENV_VAR;
// 			cur_tkn_data->str_len = ft_strlen(cur_tkn_data->str);
// 			((t_tkn_data *)(tkns_head->content))->list_size--;

static void	do_the_merge(t_tkn_data *next_cont, t_tkn_data *curr_cont,
	t_list *head, t_list *tkn)
{
	int	next_wp_status;

	next_wp_status = -1;
	next_wp_status = next_cont->white_space;
	curr_cont->str = join_two_strs(&(curr_cont->str), next_cont->str);
	if (!curr_cont->str)
		return ;//protect
	remove_next_node(head);
	curr_cont->type = TKN_WORD;
	curr_cont->white_space = next_wp_status;
	curr_cont->str_len = ft_strlen(curr_cont->str);
	((t_tkn_data *)(tkn->content))->list_size--;
}

void	merge_strings(t_list *tkn)
{
	t_list		*head;
	t_tkn_data	*curr_cont;
	t_tkn_data	*next_cont;
	int			flag;

	flag = 0;
	head = tkn;
	while (head && head->next)
	{
		flag = 0;
		curr_cont = (t_tkn_data *)head->content;
		next_cont = (t_tkn_data *)head->next->content;
		if (is_word_or_string(curr_cont->type)
			&& curr_cont->white_space == NOT_FOLLOWED_BY_WHITE_SPACE)
		{
			if (is_word_or_string(next_cont->type))
			{
				do_the_merge(next_cont, curr_cont, head, tkn);
				flag = 1;
			}
		}
		if (!flag)
			head = head->next;
	}
}
