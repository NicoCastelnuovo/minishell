/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_delnode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:35:25 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/23 12:51:35 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dlist_delnode(t_dlist **node, void (*del)(void *))
{
	t_dlist	*tmp;
	t_dlist	*prev;
	t_dlist	*next;

	tmp = NULL;
	ft_printf("\n*** *** *** *** *** *** *** *** *** *** \n");
	if (!(*node)->prev) // means it is the first node to be deleted
	{
		ft_printf(" FIRST NODE !\n");
		tmp = *node;
		(*node) = (*node)->next;
		(*node)->prev = NULL;
		del(tmp->content);
		free(tmp);
	}
	else if (!(*node)->next) // means it is the last node
	{
		ft_printf(" LAST NODE !\n");
		tmp = (*node)->prev;
		tmp->next = NULL;
		del(tmp->content);
		free(tmp);
	}
	else
	{
		ft_printf(" MID NODE !\n");
		tmp = (*node);
		prev = (*node)->prev;
		next = (*node)->next;
		prev->next = next;
		del(tmp->content);
		free(tmp);
	}
}

// void	dlist_delnode(t_dlist **node, void (*del)(void *))
// {
// 	t_dlist	*tmp;
// 	t_dlist	*prev;
// 	t_dlist	*next;

// 	tmp = NULL;
// 	ft_printf("\n*** *** *** *** *** *** *** *** *** *** \n");
// 	if (!(*node)->prev) // means it is the first node to be deleted
// 	{
// 		ft_printf(" FIRST NODE !\n");
// 		tmp = *node;
// 		(*node) = (*node)->next;
// 		(*node)->prev = NULL;
// 		del(tmp->content);
// 		free(tmp);
// 	}
// 	else if (!(*node)->next) // means it is the last node
// 	{
// 		ft_printf(" LAST NODE !\n");
// 		tmp = (*node)->prev;
// 		tmp->next = NULL;
// 		del(tmp->content);
// 		free(tmp);
// 	}
// 	else
// 	{
// 		ft_printf(" MID NODE !\n");
// 		tmp = (*node);
// 		prev = (*node)->prev;
// 		next = (*node)->next;
// 		prev->next = next;
// 		del(tmp->content);
// 		free(tmp);
// 	}
// }
