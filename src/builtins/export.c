/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:09:15 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/15 14:59:26 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	As env builtin does, it prints out the env variables, but in ASCII
	order, including the variables which are not initialized.
*/
void	get_exported(t_list *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (var->to_export)
		{
			if (var->name) // change to if (is_exported)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(var->name, 1);
			}
			if (var->value)
			{
				ft_putchar_fd('=', 1);
				ft_putchar_fd('"', 1);
				ft_putstr_fd(var->value, 1);
				ft_putchar_fd('"', 1);
			}
			ft_putchar_fd('\n', 1);
		}
		env = env->next;
	}
}

static int	env_var_exist(char *name, t_list *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (ft_strcmp(var->name, name) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

static void	update_var_content(char *name, char *new_value, t_list *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (ft_strcmp(var->name, name) == 0)
		{
			free(var->value);
			var->value = ft_strdup(new_value);
			return ;
		}
		env = env->next;
	}
}

/*
	Exports the specified variable to the subshells and child processes.
	• IF the var doesn't exist yet, a new one is created and appended
	• IF the var exist, if arg is initialized (at least = sign at the end),
		the variable need to be updated.
*/
static void	check_export(char *arg, t_list **env)
{
	t_var	*tmp_var;
	t_list	*new_node;

	new_node = NULL;
	tmp_var = NULL;
	tmp_var = create_var_content(arg);
	if (!env_var_exist(tmp_var->name, *env))
	{
		new_node = ft_lstnew(tmp_var);
		ft_lstadd_back(env, new_node);
	}
	else
	{
		if (tmp_var->value)
		{
			update_var_content(tmp_var->name, tmp_var->value, *env);
			del_var_content(tmp_var);
		}
	}
}

void	export(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)data->tree->content;
	if (!cmd->args[1])
		get_exported(data->env);
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			if (cmd->args[i][0] == '=')
			{
				// error invalid identifier
				return ;
			}
			check_export(cmd->args[i], &data->env); // needs expansion!
			i++;
		}
	}
}
