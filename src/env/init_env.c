/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 08:50:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/06 11:37:43 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	In case the environment is ignored, a minimum and essential environment is
	still created with the following variables.
*/
t_list	*create_essential_env(void)
{
	t_list	*env_cpy;
	t_list	*new_node;
	t_var	*new_content;

	env_cpy = NULL;
	new_content = create_var_content("OLDPWD"); // protect
	new_node = ft_lstnew(new_content);
	if (!new_node)
		return (ft_lstclear(&env_cpy, del_var_content), NULL); // free()
	ft_lstadd_back(&env_cpy, new_node);
	new_content = create_var_content("PWD"); // protect
	new_content->value = get_wd(); // protect
	new_content->value_len = ft_strlen(new_content->value);
	new_node = ft_lstnew(new_content);
	if (!new_node)
		return (ft_lstclear(&env_cpy, del_var_content), NULL); // free()
	ft_lstadd_back(&env_cpy, new_node);
	new_content = create_var_content("SHLVL"); // protect
	new_content->value = ft_strdup("1");
	new_content->value_len = 1;
	new_node = ft_lstnew(new_content);
	if (!new_node)
		return (ft_lstclear(&env_cpy, del_var_content), NULL); // free()
	ft_lstadd_back(&env_cpy, new_node);
	return (env_cpy);
}

static int	oldpwd_exists(t_list *env_cpy)
{
	t_list	*head;
	t_var	*var;

	head = env_cpy;
	while (head)
	{
		var = (t_var *)head->content;
		if (ft_strcmp(var->name, "OLDPWD") == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

static int	create_oldpwd(t_list *env_cpy)
{
	t_list	*new_node;
	t_var	*new_content;

	new_node = NULL;
	if (!oldpwd_exists(env_cpy))
	{
		new_content = create_var_content("OLDPWD"); // protect
		new_node = ft_lstnew(new_content);
		if (!new_node)
			return (ft_lstclear(&env_cpy, del_var_content), 1); // free()
		ft_lstadd_back(&env_cpy, new_node);
	}
	return (0);
}

/*
	Copies the environment variable of the parent process into a double
	linked list, to be used in the current shell.
*/
t_list	*init_env(char **env)
{
	t_list	*env_cpy;
	t_list	*new_node;
	t_var	*new_content;
	int		i;

	env_cpy = NULL;
	new_node = NULL;
	i = 0;
	if (!env[i])
		env_cpy = create_essential_env();
	while (env[i])
	{
		new_content = create_var_content(env[i]); // protect
		new_node = ft_lstnew(new_content);
		if (!new_node)
			return (ft_lstclear(&env_cpy, del_var_content), NULL); // free()
		ft_lstadd_back(&env_cpy, new_node);
		i++;
	}
	if (create_oldpwd(env_cpy))
		return (ft_lstclear(&env_cpy, del_var_content), NULL); // free()
	return (env_cpy);
}
