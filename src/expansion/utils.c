/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 08:02:20 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/19 09:25:45 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var_lst(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	free(var);
}

void	print_var_lst(t_list *var_lst)
{
	t_list *head;

	head = var_lst;
	while (head)
	{
		if (head->content)
		{
			ft_printf("name [%s]", ((t_var *)head->content)->name);
			ft_printf("[%d] - ", ((t_var *)head->content)->name_len);
			ft_printf("value [%s]", ((t_var *)head->content)->value);
			ft_printf("[%d]\n", ((t_var *)head->content)->value_len);
		}
		head = head->next;
	}
	ft_printf("________\n\n");
}
