/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:03:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 12:43:28 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var	*copy_var_content(t_var *var)
{
	t_var	*new_content;

	new_content = ft_calloc(1, sizeof(t_var));
	if (!new_content)
		return (NULL);
	new_content->name = NULL;
	new_content->name_len = -1;
	new_content->value = NULL;
	new_content->value_len = -1;
	if (var->name)
	{
		new_content->name = ft_strdup(var->name);
		if (!new_content->name)
			return (free(new_content), NULL);
		new_content->name_len = var->name_len;
	}
	if (var->value)
	{
		new_content->value = ft_strdup(var->value);
		if (!new_content->value)
			return (free(new_content), NULL);
		new_content->value_len = var->value_len;
	}
	return (new_content);
}

t_list	*cpy_env(t_list *old)
{
	t_list	*new_list;
	t_list	*new_node;
	t_var	*new_content;
	t_var	*var;

	new_list = NULL;
	new_content = NULL;
	while (old)
	{
		var = (t_var *)old->content;
		new_content = copy_var_content(var);
		if (!new_content)
			return (ft_lstclear(&new_list, del_var_content), NULL);
		new_node = ft_lstnew(new_content);
		if (!new_node)
			return (ft_lstclear(&new_list, del_var_content), NULL);
		ft_lstadd_back(&new_list, new_node);
		old = old->next;
	}
	return (new_list);
}

/* static void	sort(t_list **env)
{
	// need to sort based on ASCII value!
	// idea: swap just the contents, not the node
} */

t_list	*sort_env(t_list *old)
{
	t_list	*env_cpy;

	env_cpy = cpy_env(old);
	if (!env_cpy)
		return (NULL);
	// sort(&env_cpy);
	print_env(env_cpy);
	exit (0);
	return (env_cpy);
}
