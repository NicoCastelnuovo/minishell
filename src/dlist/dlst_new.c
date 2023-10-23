/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:34:43 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/23 11:05:35 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*dlst_new(void *content)
{
	t_dlist	*new_list;

	new_list = (t_dlist *)malloc(sizeof(t_dlist));
	if (!new_list)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	new_list->prev = NULL;
	return (new_list);
}
