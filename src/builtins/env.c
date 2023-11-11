/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:16:10 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/11 15:17:00 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Outputs the environment variables which are at least an empty string. The
	uninitalized env var are not output like in the standar env builtin.
*/
void	env(t_env *env)
{
	t_var	*head;

	head = env->head;
	ft_printf("\033[0;36m============= ENVIRONMENT =============\033[0;37m\n");
	if (env->size)
	{
		while (head)
		{
			if (head->name && head->value)
			{
				ft_putstr_fd(head->name, 1);
				ft_putchar_fd('=', 1);
				ft_putendl_fd(head->value, 1);
			}
			head = head->next;
		}
	}
	ft_printf("\033[0;36m=======================================\033[0;37m\n");
}
