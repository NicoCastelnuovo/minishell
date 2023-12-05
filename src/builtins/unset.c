/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:37:54 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/05 17:26:06 by ncasteln         ###   ########.fr       */
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
int	unset(t_cmd *cmd, t_data *data)
{
	int		i;

	if (!cmd->args[1])
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		if (is_invalid_identifier(cmd->args[0], cmd->args[i]))
			return (1);
		unset_single_var(cmd->args[i], &data->env);
		i++;
	}
	return (0);
}
