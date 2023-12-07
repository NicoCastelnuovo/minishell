/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:09:15 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 16:02:44 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	As env builtin does, it prints out the env variables, but in ASCII
	order, including the variables which are not initialized.
*/

/* t_list	*copy(t_list *env)
{
	t_list	**head;
	t_list	*new;
	t_var	*var;

	head = NULL;
	while (env)
	{
		var = ft_calloc(1, sizeof(t_var));
		new = ft_lstnew(var);
		ft_lstadd_back(head, new);
		var->name = ft_strdup(((t_var *)(env->content))->name);
		var->name_len = ((t_var *)(env->content))->name_len;
		var->value = ft_strdup(((t_var *)(env->content))->value);
		var->value_len = ((t_var *)(env->content))->value_len;
		env = env->next;
	}
	
}

void	print_env_copy(t_list *env_copy)
{
	while (env_copy)
	{
		printf("name = %s\n", ((t_var *)(env_copy->content))->name);
		printf("name_len = %s\n", ((t_var *)(env_copy->content))->name_len);
		printf("value = %s\n", ((t_var *)(env_copy->content))->value);
		printf("value_len = %s\n", ((t_var *)(env_copy->content))->value_len);
		env_copy = env_copy->next;
	}
	
} */

void	print_dptr_contetnt(char **dptr)
{
	int	i;

	i = 0;
	while (dptr[i])
	{
		printf("%s\n", dptr[i]);
		i++;
	}
	
}

void	print_all_env(t_list *env)
{
	while (env)
	{
		printf("%s\n", ((t_var *)(env->content))->name);
		env = env->next;
	}
	
}



/* char	**env_convert_to_double_pointer(t_list *env)
{
	char	**env_dptr;
	int		i;
	char	*name_value;
	char	*temp;
	
	i = 0;
	env_dptr = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	while (env)
	{
		name_value = ft_strjoin(((t_var *)(env->content))->name, "=");
		temp = name_value;
		name_value = ft_strjoin(name_value, "\"");
		free(temp);
		temp = name_value;
		if (((t_var *)(env->content))->value)
			name_value = ft_strjoin(name_value, ((t_var *)(env->content))->value);
		else
		{
			name_value = ft_strjoin(name_value, "\"");
			env_dptr[i] = name_value;
			free(temp);
			env = env->next;
			i++;
			continue ;
		}
		free(temp);
		temp = name_value;
		name_value = ft_strjoin(name_value, "\"");
		free(temp);
		env_dptr[i] = name_value;
		ft_printf("🤬\n");
		env = env->next;
		i++;
	}
	
	return (env_dptr);
} */

char	**env_convert_to_double_pointer(t_list *env)
{
	char	**env_dptr;
	int		i;
	char	*name_value;
	char	*temp;
	
	i = 0;
	env_dptr = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	while (env)
	{
		if (((t_var *)(env->content))->value)
		{
			name_value = ft_strjoin(((t_var *)(env->content))->name, "=");
			temp = name_value;
			name_value = ft_strjoin(name_value, ((t_var *)(env->content))->value);
			free(temp);
		}
		else
			name_value = ft_strdup(((t_var *)(env->content))->name);
		env_dptr[i] = name_value;
		env = env->next;
		i++;
	}
	return (env_dptr);
}

char	**sort_export(t_list *env)
{
	char	**env_dptr;
	int	i;
	int	j;
	char	*temp;

	i = 0;
	// print_all_env(env);
	env_dptr = env_convert_to_double_pointer(env);
	while (env_dptr[i])
	{
		j = i + 1;
		while (env_dptr[j])
		{
			if (env_dptr[i][0] > env_dptr[j][0])
			{
				temp = env_dptr[j];
				env_dptr[j] = env_dptr[i];
				env_dptr[i] = temp;
			}
			j++;
		}
		i++;
	}
	// print_dptr_contetnt(env_dptr);
	return (env_dptr);
}

/* char	*add_double_quotes(char *sorted_env)
{
	char	*quoted_name_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quoted_name_value = ft_calloc(ft_strlen(sorted_env) + 3, sizeof(char));
	while (*sorted_env)
	{
		if (sorted_env[i] == '=')
		{
			quoted_name_value[i] = '"';
			quoted_name_value[i + 1] = sorted_env[j];
			
		}
		quoted_name_value[i] = sorted_env[j];
		sorted_env++;
		i++;
		j++;
	}
	
} */

int	print_exported(t_list *env)
{
	// t_var	*var;
	char	**sorted_env;
	// char	*quoted_name_value;
	int		i;

	i = 0;
	sorted_env = sort_export(env);
	while (*sorted_env)
	{
		while (**sorted_env)
		{
			printf("%c", (**sorted_env));
			(*sorted_env)++;
		}
		sorted_env++;
		printf("\n");
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

/* static void	append_to_existing_var(t_list *env, t_var *tmp_var)
{
	t_list	*head;
	t_var	*var;
	(void)tmp_var;
	head = env;
	while (head)
	{
		var = (t_var *)head->content;

		head = head->next;
	}
} */


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
				tmp = var->value;
				var->value = ft_strjoin(var->value, new_value); // protect
				if (!var->value)
					return (1);
				free(tmp);
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
	char	*tmp;

	(void)tmp;
	new_node = NULL;
	tmp_var = NULL;
	tmp_var = create_var_content(arg);
	if (!env_var_exist(tmp_var->name, *env))
	{
		new_node = ft_lstnew(tmp_var); // protect
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





/*
	take the first part of the string until = or the entire word
	print "
	print the right part of the first =
	print "

*/