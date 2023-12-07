/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:20:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 10:32:47 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_wd(void)
{
	char	*buff;
	size_t	size;

	buff = NULL;
	size = 1;
	buff = ft_calloc(size + 1, sizeof(char));
	if (!buff)
		return (NULL);
	buff = getcwd(buff, size);
	while (!buff)
	{
		free(buff);
		size += 1;
		buff = ft_calloc(size + 1, sizeof(char));
		if (!buff)
			return (NULL);
		buff = getcwd(buff, size);
	}
	return (buff);
}

static int	create_new_var(char *name, char *new_value, t_list **env)
{
	char	*env_var;
	char	*tmp;
	t_var	*new_var;
	t_list	*new_node;

	new_var = NULL;
	tmp = NULL;
	env_var = ft_strjoin(name, "=");
	if (!env_var)
		return (1);
	tmp = env_var;
	env_var = ft_strjoin(env_var, new_value);
	if (!env_var)
		return (1);
	free(tmp);
	new_var = create_var_content(env_var);
	free(env_var);
	if (!new_var)
		return (1);
	new_node = ft_lstnew(new_var);
	if (!new_node)
		return (del_var_content(new_var), 1);
	ft_lstadd_back(env, new_node);
	return (0);
}

/*
	Update the existing variables OLDPWD and PWD. If They are not found in the
	list, then they are created. To test it, unset OLDPWD and PWD, and than
	run the builtin 'cd'.
*/
static int	update_var_or_create(char *name, char *new_value, t_list **env)
{
	t_list	*head;
	t_var	*var;

	head = (*env);
	while (head)
	{
		var = (t_var *)head->content;
		if (ft_strcmp(name, var->name) == 0)
		{
			var->value = new_value;
			var->value_len = ft_strlen(new_value);
			return (0);
		}
		head = head->next;
	}
	if (create_new_var(name, new_value, env))
		return (1);
	return (0);
}

/*
	cd changes the current working directory of the current shell env. Only a
	relative or an absolute path are accepted.
*/
int	cd(t_cmd *cmd, t_data *data)
{
	char	*destination;
	char	*curr_pwd;
	char	*new_abs_path;

	curr_pwd = get_wd();
	if (!curr_pwd)
		return (error("cd", NULL, errno), 1);
	destination = cmd->args[1];
	if (!destination)
		destination = get_env_custom("HOME", data->env);
	if (chdir(destination) == -1)
	{
		free(curr_pwd);
		return (error("cd", destination, errno), 1);
	}
	else
	{
		update_var_or_create("OLDPWD", curr_pwd, &data->env); // protect
		new_abs_path = get_wd();
		if (!new_abs_path)
			return (error("cd", NULL, errno), 1);
		update_var_or_create("PWD", new_abs_path, &data->env); // protect
	}
	return (0);
}
