/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:37:54 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/23 17:03:52 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	dlist_deltop(t_dlist **node, void (*del)(void *))
{
	t_dlist	*tmp;

	ft_printf(" [FIRST NODE]\n");
	ft_printf("- - - - - - - - - - - - - - - - - - - - - -\n");
	tmp = *node;
	(*node) = (*node)->next;
	(*node)->prev = NULL;
	del(tmp->content);
	free(tmp);
}

static void	dlist_delmid(t_dlist **node, void (*del)(void *))
{
	t_dlist	*next_node;
	t_dlist	*prev_node;

	ft_printf(" [MID NODE]\n");
	ft_printf("- - - - - - - - - - - - - - - - - - - - - -\n");
	next_node = (*node)->next; // next is node of TERM_PROGRAM
	prev_node = (*node)->prev; // prev is node of SHELL
	prev_node->next = next_node;
	next_node->prev = prev_node;
	del((*node)->content);
	free(*node);
}

static void	dlist_dellast(t_dlist *node, void (*del)(void *))
{
	ft_printf(" [LAST NODE]\n");
	ft_printf("- - - - - - - - - - - - - - - - - - - - - -\n");
	del(node->content);
	free(node);
	node->prev->next = NULL;
}

/*
	The environment variable specified by <name> is unset for the current
	environment. If the argument is a variable which doesn't exist, nothing
	happens.
*/
void	unset_env_var(char *name, t_dlist **env)
{
	t_var	*var;
	t_dlist	*head;

	head = *env;
	while (head)
	{
		var = (t_var *)head->content;
		if (ft_strncmp(name, var->name, var->name_len) == 0)
		{
			ft_printf("- - - - - - - - - - - - - - - - - - - - - -\n");
			ft_printf("need to remove [%s] len of %d \n", var->name, var->name_len);
			ft_printf("need to remove [%s] len of %d ", var->value, var->value_len);
			if (!head->prev)
				dlist_deltop(env, del_var_lst_content);
			else if (!head->next)
				dlist_dellast(head, del_var_lst_content);
			else
				dlist_delmid(&head, del_var_lst_content);
			break ;
		}
		head = head->next;
	}
}

// ft_printf("head = {%s} ", ((t_var *)(*head)->content)->name);
// ft_printf("env = {%s}\n\n", ((t_var *)(*env)->content)->name);


// void	unset_env_var(char *name, t_dlist **env)
// {
// 	t_var	*var;
// 	t_dlist	**head;

// 	head = env;
// 	while (*head)
// 	{
// 		var = (t_var *)(*head)->content;
// 		if (ft_strncmp(name, var->name, var->name_len) == 0)
// 		{
// 			dlist_delnode(head, del_var_lst_content);
// 			break ;
// 		}
// 		(*head) = (*head)->next;
// 	}
// }

// // ft_printf("head = {%s} ", ((t_var *)(*head)->content)->name);
// // ft_printf("env = {%s}\n\n", ((t_var *)(*env)->content)->name);
