/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:37:54 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/15 14:59:21 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_single_var(char *name, t_list **env)
{
	t_list	*head;
	t_list	*next_node;

	head = (*env);
	while (head)
	{
		if (head == (*env))
		{
			if (ft_strcmp(((t_var *)head->content)->name, name) == 0)
			{
				ft_lstdelone(head, del_var_content);
				(*env) = (*env)->next;
				break ;
			}
		}
		if (head->next)
		{
			next_node = (t_list *)head->next;
			if (ft_strcmp(((t_var *)next_node->content)->name, name) == 0)
			{
				head->next = next_node->next;
				ft_lstdelone(next_node, del_var_content);
				break ;
			}
		}
		head = head->next;
	}
}

/*
	The environment variable specified by <name> is unset for the current
	environment. If the argument is a variable which doesn't exist, nothing
	happens.
*/
int	unset(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)data->tree->content;
	i = 1;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '='))
		{
			error("unset", cmd->args[i], 1);
			data->e_code = 1;
			return (1);
		}
		unset_single_var(cmd->args[i], &data->env);
		i++;
	}
	return (0);
}
