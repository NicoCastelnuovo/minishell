/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:09:15 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/08 11:22:40 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	As env builtin does, it prints out the env variables, but in ASCII
	order, including the variables which are not initialized.
*/
int	print_exported(t_list *env)
{
	t_var	*var;
	t_list	*sorted;

	sorted = NULL;
	// if (env)
	// {
	// 	sorted = sort_env(env);
	// 	if (!sorted)
	// 		return (1);
	// 	else
	// 	{
	// 		// print sorted
	// 	}
	// }
	// change printing
	while (env)
	{
		var = (t_var *)env->content;
		if (var)
		{
			if (var->name) // change to if (is_exported) ??
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
	return (0);
}

/*
	@param n: number of charachter to compare. It is needed to differentiate
	between var+=value which append value to the var, and var=value, which
	assigns it truncating the already existing content.
*/
static int	env_var_exist(char *tmp_var_name, t_list *env)
{
	t_var	*var;
	int		n;

	n = ft_strlen(tmp_var_name);
	if (tmp_var_name[n - 1] == '+')
		n -= 1;
	while (env)
	{
		var = (t_var *)env->content;
		if (ft_strncmp(var->name, tmp_var_name, n) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

static int	append_to_existing_var(t_var *var, char *new_value)
{
	char	*tmp;

	tmp = var->value;
	var->value = ft_strjoin(var->value, new_value);
	if (!var->value)
		return (1);
	free(tmp);
	return (0);
}

static int	update_var_content(char *name, char *new_value, t_list *env)
{
	t_var	*var;
	int		n;
	char	*tmp;

	tmp = NULL;
	n = ft_strlen(name);
	if (name[n - 1] == '+')
		n -= 1;
	while (env)
	{
		var = (t_var *)env->content;
		if (ft_strncmp(var->name, name, n) == 0)
		{
			if (name[n] == '+')
			{
				if (append_to_existing_var(var, new_value))
					return (1);
			}
			else
			{
				free(var->value);
				var->value = ft_strdup(new_value);
				if (!var->value)
					return (1);
			}
		}
		env = env->next;
	}
	return (0);
}

/*
	Exports the specified variable to the subshells and child processes.
	• IF the var doesn't exist yet, a new one is created and added to the env
	• IF the var exist, if arg is initialized (at least = sign at the end),
		the variable need to be replaced. If at the left ofthe equal sign there
		is a + , than the old value is not replaces, but the new one is
		appended.
*/
static int	check_export(char *arg, t_list **env)
{
	t_var	*tmp_var;
	t_list	*new_node;

	new_node = NULL;
	tmp_var = NULL;
	tmp_var = create_var_content(arg);
	if (!env_var_exist(tmp_var->name, *env))
	{
		new_node = ft_lstnew(tmp_var);
		if (!new_node)
			return (1);
		ft_lstadd_back(env, new_node);
	}
	else
	{
		if (tmp_var->value)
		{
			if (update_var_content(tmp_var->name, tmp_var->value, *env))
				return (1);
			del_var_content(tmp_var);
		}
	}
	return (0);
}

static int	is_valid_export_identifier(char *arg)
{
	int	i;
	int	assigned;

	if (arg[0] == '=' || ft_isdigit(arg[0]))
		return (error("export", arg, CE_INVALIDIDENTIFIER), 0);
	assigned = 0;
	i = 0;
	while (arg[i])
	{
		if (!assigned)
		{
			if (arg[i] == '=')
				assigned = 1;
			else if (arg[i] == '+' && arg[i + 1] == '=')
				return (1);
			else if (!ft_isalnum(arg[i]) && arg[i] != '_')
				return (error("export", arg, CE_INVALIDIDENTIFIER), 0);
		}
		i++;
	}
	return (1);
}

int	export(t_cmd *cmd, t_data *data)
{
	int	i;

	if (!cmd->args[1])
		print_exported(data->env);
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			if (is_valid_export_identifier(cmd->args[i]))
			{
				if (check_export(cmd->args[i], &data->env))
					return (1);
			}
			i++;
		}
	}
	return (0);
}
