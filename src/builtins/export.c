/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:09:15 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/06 12:21:15 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	As env builtin does, it prints out the env variables, but in ASCII
	order, including the variables which are not initialized.
*/
void	print_exported_env(t_env *env)
{
	t_var	*head;

	head = env->head;
	if (env->size)
	{
		while (head)
		{
			if (head->name)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(head->name, 1);
			}
			if (head->value)
			{
				ft_putchar_fd('=', 1);
				ft_putchar_fd('"', 1);
				ft_putstr_fd(head->value, 1);
				ft_putchar_fd('"', 1);
			}
			ft_putchar_fd('\n', 1);
			head = head->next;
		}
	}
}

/*
	The function returns (1) if finds an already set environment variable
	with the same name as new_content->name.
*/
static int	env_var_already_set(t_var *new_node, t_env **env)
{
	t_var	*head;

	head = (*env)->head;
	while (head)
	{
		if (ft_strncmp(head->name, new_node->name, head->name_len) == 0) // used to check ex. USER and USERUSER
		{
			if (head->name_len == new_node->name_len)
				return (1);
		}
		head = head->next;
	}
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
void	export(char *arg, t_env **env)
{
	t_var	*new_node;

	if (!arg)
	{
		print_exported_env(*env);
		return ;
	}
	new_node = env_dlst_new(arg);
	if (env_var_already_set(new_node, env))
	{
		if (new_node->value)
			env_dlst_update(new_node, env);
		else
			free_env_node(new_node);
		return ;
	}
	else
		env_dlst_append(env, new_node);
}
