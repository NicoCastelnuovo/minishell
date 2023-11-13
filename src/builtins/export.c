/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:09:15 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/13 11:20:16 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	As env builtin does, it prints out the env variables, but in ASCII
	order, including the variables which are not initialized.
*/
void	print_exported_env(t_env *env)
{
	// t_var	*head;

	// head = env->head;
	// if (env->size)
	// {
	// 	while (head)
	// 	{
	// 		if (head->name) // change to if (is_exported)
	// 		{
	// 			ft_putstr_fd("declare -x ", 1);
	// 			ft_putstr_fd(head->name, 1);
	// 		}
	// 		if (head->value)
	// 		{
	// 			ft_putchar_fd('=', 1);
	// 			ft_putchar_fd('"', 1);
	// 			ft_putstr_fd(head->value, 1);
	// 			ft_putchar_fd('"', 1);
	// 		}
	// 		ft_putchar_fd('\n', 1);
	// 		head = head->next;
	// 	}
	// }
}

/*
	The function returns (1) if finds an already set environment variable
	with the same name as new_content->name.
*/
static int	env_var_already_set(t_var *new_node, t_env **env)
{
	t_var	*head;

	// head = (*env)->head;
	// while (head)
	// {
	// 	if (ft_strcmp(head->name, new_node->name) == 0) // used to check ex. USER and USERUSER
	// 		return (1);
	// 	head = head->next;
	// }
	return (0);
}

/*
	Exports the specified variable to the subshells and child processes.
	If arg is NULL, the exported env is printed with the correct format.
	Then checks if the var already exists:
		- if exists and there is a new value, then the new_content
		replaces the node (ex. USER= is the minimum accepted).
		- if exist and there is not new value (ex. USER), then there
		is no update for the content.
		- if doesn't exist, a new variable is created.
*/
static void	check_export(char *arg, t_env **env)
{
	t_var	*new_node;

	new_node = NULL;
	// new_node = env_dlst_new(arg);
	if (env_var_already_set(new_node, env))
	{
		// ft_printf("--------------VAR SET, CHECK STATUS ----------------\n");
		if (new_node->value)
		{
			// ft_printf("-------------- A NEW VALUE HAS TO BE SET ----------------\n");
			// env_dlst_update(new_node, env);
			ft_printf("	PROBLEM HERE IN DLST UPDATE!!!!! THIS IS NOT PRINTED \n");
		}
		else
		{
			// ft_printf("-------------- {\033[0;31m NO \033[0;37m} VALUE TO BE SET ----------------\n");
			// free_env_node(new_node);
		}
		return ;
	}
	else
	{
		// ft_printf("{\033[0;31m I WANT TO APPEND A NEW VAR \033[0;37m}\n");
		// problem with [export SHIT SHIT=MERDA]
		// env_dlst_append(env, new_node);
	}
}

void	export(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)data->tree->content;
	if (!cmd->args[1])
		print_exported_env(data->env);
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			/*
				NEED TO VALIDATE THE NAME FOR EXPORT
			*/
			check_export(cmd->args[i], &data->env); // needs expansion!
			i++;
		}
	}
}
