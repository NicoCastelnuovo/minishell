/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:09:15 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/26 13:20:02 by ncasteln         ###   ########.fr       */
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
				ft_putstr_fd(head->name, 1);
			if (head->value)
				ft_putstr_fd(head->value, 1);
			ft_putchar_fd('\n', 1);
			head = head->next;
		}
	}
}

static int	env_var_already_set(char *arg, t_env **env)
{
	int		name_len;
	char	*name;
	t_var	*head;
	char	*tmp;

	name_len = get_substr_len(arg, '=');
	name = ft_substr(arg, 0, name_len + 1); // + 1 take the =
	head = (*env)->head;
	while (head)
	{
		if (ft_strncmp(head->name, name, head->name_len) == 0)
			return (free(name), 1);
		head = head->next;
	}
	return (free(name), 0);
}

/*
	NOTES:
	-	export should work with more than one variable (pd)
	-	unspecified result if no argument
	-	what should do a part of setting a varible? It is exported to a subprocess
		but what how can I prove it? Should we handle the VAR=value syntax ??
*/
/*
	Exports the specified variable to the subshells and child processes.
	@line	if (name[name_len - 1] == '='): prevents the variable to be
			modified by a non-initialized variable (example:
			export HELLO=world; export HELLO)'
*/
void	export(char *arg, t_env **env)
{
	char	*name;
	char	*value;
	int		name_len;
	t_var	*new_content;
	t_var	*new_node;

	if (!arg)
	{
		print_exported_env(*env);
		return ;
	}
	if (env_var_already_set(arg, env)) // assumes that input ends with =
	{
		env_dlst_update(arg, env);
		return ;
	}
	else // create but pay attention how
	{
		// free(name);
		// new_content = prepare_env_content(arg); // protect
		// new_node = env_dlst_new(new_content); // protect
		// free(new_content);
		// env_dlst_append(env, new_node);
	}
}
