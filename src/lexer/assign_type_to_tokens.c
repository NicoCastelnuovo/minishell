/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_type_to_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:33:17 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/30 12:33:55 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_type_to_tkn(t_list *tkns_head)
{
	t_list		*temp;
	t_tkn_data	*tkn_data;

	temp = tkns_head;
	while (temp)
	{
		tkn_data = (t_tkn_data *)(temp->content);
		check_each_tkn_str(tkn_data);
		temp = temp->next;
	}
}
