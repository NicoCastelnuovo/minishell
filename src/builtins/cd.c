/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:20:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 09:54:39 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_wd(void)
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

static void	update_existing_var(char *name, char *new_value, t_list **env)
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
			return ;
		}
		head = head->next;
	}
}

/*
	cd changes the current working directory of the current shell env. Only a
	relative or an absolute path are accepted.
*/
int	cd(t_data *data)
{
	char	*destination;
	char	*curr_pwd;
	char	*new_abs_path;

	curr_pwd = get_wd();
	if (!curr_pwd)
		return (error("cd", NULL, errno), 1);
	destination = ((t_cmd *)data->tree->content)->args[1];
	if (!destination)
		destination = get_env_custom("HOME", data->env);
	if (chdir(destination) == -1)
	{
		free(curr_pwd);
		return (error("cd", destination, errno), 1);
	}
	else
	{
		update_existing_var("OLDPWD", curr_pwd, &data->env);
		new_abs_path = get_wd();
		if (!new_abs_path)
			return (error("cd", NULL, errno), 1);
		update_existing_var("PWD", new_abs_path, &data->env);
	}
	return (0);
}
