/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:18:55 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/19 10:57:54 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Take as argument a string without dollar sign included. It checks
	immediately if the parameter is $?, which is not an env var, but a Shell
	built-in variable.
*/
static int	get_var_name_len(char *s)
{
	int	i;

	if (s[0] == '?')
		return (1);
	i = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

static int	get_n_dollars(char *s)
{
	int	n;

	n = 0;
	while (*s)
	{
		if (*s == '$')
			n++;
		s++;
	}
	return (n);
}

/*
	For each variable name in the list, getenv() is applied, and the value is
	duplicated into the node. If the variable doesn't exist, an empty string
	is duplicated.
*/
static void	get_var_values(t_list *var_lst, int n, int exit_code)
{
	char	*expanded;
	t_var	*var;

	while (var_lst)
	{
		var = (t_var *)var_lst->content;
		if (ft_strncmp(var->name, "$", 1) == 0)
			expanded = ft_strdup("$");
		else
		{
			if (ft_strncmp(var->name, "?", 1) == 0)
				expanded = ft_itoa(exit_code);
			else
			{
				if (getenv(var->name))
					expanded = ft_strdup(getenv((var->name)));
				else
					expanded = ft_strdup("");
			}
		}
		var->value = expanded;
		var->value_len = ft_strlen(var->value);
		var_lst = var_lst->next;
	}
}

/*
	Based on the number of $ sign found in the string, the function returns
	a list whose content has the variable name to expand, and the length of it.
*/
static t_list	*get_var_names(char *s, int n)
{
	t_list	*var_lst;
	t_list	*new_node;
	t_var	*var;
	int		i;

	var_lst = NULL;
	i = 0;
	while (i < n)
	{
		var = ft_calloc(1, sizeof(t_var));
		if (!var)
			return (ft_lstclear(&var_lst, del_var_lst), NULL);
		s = ft_strchr(s, '$');
		s++;
		var->name_len = get_var_name_len(s);
		if (var->name_len == 0)
			var->name = ft_strdup("$");
		else
			var->name = ft_substr(s, 0, var->name_len);
		if (!var->name)
			return (ft_lstclear(&var_lst, del_var_lst), NULL);
		var->value = NULL;
		var->value_len = -1;
		new_node = ft_lstnew(var); // protect
		ft_lstadd_back(&var_lst, new_node);
		i++;
	}
	return (var_lst);
}

/*
	Just perform the expansion on a string which needs it. The check to
	understand if the string needs to be expanded is done before.
*/
char	*expansion(char *s, int exit_code)
{
	int		n;
	t_list	*var_lst;
	char	*new_str;

	n = get_n_dollars(s);
	var_lst = get_var_names(s, n);
	get_var_values(var_lst, n, exit_code);
	new_str = build_str(s, var_lst);

	print_var_lst(var_lst); // remove
	ft_printf("old_str: [%s]\n", s);
	ft_printf("new_str: [%s]\n", new_str);

	ft_lstclear(&var_lst, del_var_lst);
	return (new_str);
}
