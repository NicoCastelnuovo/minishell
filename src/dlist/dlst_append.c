/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:33:39 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/25 10:22:44 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dlst_append(t_dlist **lst, t_dlist *new)
{
	t_dlist	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = dlst_last(*lst);
	last->next = new;
	new->prev = last;
}
