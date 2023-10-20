/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 08:02:20 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/20 16:02:19 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var_lst(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	if (var)
	{
		if (var->name)
			free(var->name);
		if (var->value)
			free(var->value);
		free(var);
	}
}

void	print_var_lst(t_list *var_lst)
{
	t_var	*var;

	while (var_lst)
	{
		if (var_lst->content)
		{
			var = (t_var *)var_lst->content;
			ft_printf("name [%s]", var->name);
			ft_printf("[%d] - ", var->name_len);
			ft_printf("value [%s]", var->value);
			ft_printf("[%d]\n", var->value_len);
		}
		var_lst = var_lst->next;
	}
	ft_printf("________\n\n");
}
