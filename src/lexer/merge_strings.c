/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:35:23 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/22 12:12:25 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_word_or_string(t_tkn_type type)
{
	if (type == TKN_WORD || type == TKN_S_QUOTED_STR || type == TKN_D_QUOTED_STR || type == TKN_ENV_VAR)
		return (1);
	return (0);
}

// 			cur_tkn_data->str = join_two_strs(&(cur_tkn_data->str),
// 					next_tkn_data->str);
// 			remove_next_node(cur_node);
// 			cur_tkn_data->type = TKN_ENV_VAR;
// 			cur_tkn_data->str_len = ft_strlen(cur_tkn_data->str);
// 			((t_tkn_data *)(tkns_head->content))->list_size--;


void	merge_strings(t_list *tkn)
{
	t_list		*head;
	t_tkn_data	*curr_cont;
	t_tkn_data	*next_cont;
	int			next_wp_status;
	int			flag;

	flag = 0;
	next_wp_status = -1;
	head = tkn;
	curr_cont = NULL;
	next_cont = NULL;
	while (head && head->next)
	{
		flag = 0;
		curr_cont = (t_tkn_data *)head->content;
		// ft_printf("Curr content is [%s]\n", curr_cont->str);
		next_cont = (t_tkn_data *)head->next->content;
		// ft_printf("Next content is [%s]\n", next_cont->str);
		if (is_word_or_string(curr_cont->type) && curr_cont->white_space == NOT_FOLLOWED_BY_WHITE_SPACE)
		{
			if (is_word_or_string(next_cont->type))
			{
				next_wp_status = next_cont->white_space;
				curr_cont->str = join_two_strs(&(curr_cont->str), next_cont->str);
				if (!curr_cont->str)
					return ; // protect
				remove_next_node(head);
				curr_cont->type = TKN_WORD;
				curr_cont->white_space = next_wp_status;
				curr_cont->str_len = ft_strlen(curr_cont->str);
				((t_tkn_data *)(tkn->content))->list_size--;
				flag = 1;
			}
		}
		if (!flag)
			head = head->next;
	}
}
