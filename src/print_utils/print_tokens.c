/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:13:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/02 12:13:42 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_list *tokens)
{
	t_list *temp = tokens;
	while (temp)
	{
		t_tkn_data *tkn_data = (t_tkn_data *)temp->content;
		if (tkn_data->type == 1)
			ft_printf("[%s]	type -> [%c]\n", tkn_data->str, 'w');
		else
			ft_printf("[%s]	type -> [%c]\n", tkn_data->str, tkn_data->type);
		temp = temp->next;
	}
}
