/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:18:55 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/24 14:56:43 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_to_expand(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	if (var)
	{
		if (var->name)
			free(var->name);
		if (var->value)
			free(var->value);
		var->name_len = -1;
		var->value_len = -1;
		// var->next = NULL;
		// var->prev = NULL;
		var->to_export = -1;
		free(var);
		var = NULL;
	}
}

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
	For each variable name in the list, get_env_custom() is applied, and the value is
	duplicated into the node. If the variable doesn't exist, an empty string
	is duplicated.
*/
static void	get_var_values(t_list *var_to_expand, t_list *env, int e_code)
{
	char	*expanded;
	t_var	*var;

	expanded = NULL;
	while (var_to_expand)
	{
		var = (t_var *)var_to_expand->content;
		if (var->name_len == 0)
			expanded = ft_strdup("$");
		else if (var->name[0] == '?' && var->name_len == 1)
			expanded = ft_itoa(e_code);
		else if (get_env_custom(var->name, env))
			expanded = ft_strdup(get_env_custom(var->name, env));
		else
			expanded = ft_strdup("");
		var->value = expanded;
		var->value_len = ft_strlen(var->value);
		var_to_expand = var_to_expand->next;
	}
}

static t_list	*get_var_names(char *s, int n)
{
	t_list	*var_to_expand;
	t_list	*new_node;
	t_var	*var;
	int		i;

	var_to_expand = NULL;
	i = 0;
	while (i < n)
	{
		var = ft_calloc(1, sizeof(t_var));
		if (!var)
			return (ft_lstclear(&var_to_expand, del_to_expand), NULL);
		s = ft_strchr(s, '$');
		s++;
		var->name_len = get_var_name_len(s);
		if (var->name_len == 0)
			var->name = ft_strdup("$");
		else
			var->name = ft_substr(s, 0, var->name_len);
		if (!var->name)
			return (ft_lstclear(&var_to_expand, del_to_expand), NULL);
		var->value = NULL;
		var->value_len = -1;
		new_node = ft_lstnew(var); // protect
		if (!new_node)
			return (ft_lstclear(&var_to_expand, del_to_expand), NULL);
		ft_lstadd_back(&var_to_expand, new_node);
		i++;
	}
	return (var_to_expand);
}

/*
	In order: get n of pssible expansion to perform ("$$$" are still counted
	as three potential expansion to be done), extract the variable names
	("$" is still a variable name), get the variable values and build the
	new string which will replace the origial one.
*/
char	*expand(char *old_str, t_list *env, int e_code)
{
	int		n;
	t_list	*to_expand;
	char	*new_str;

	n = get_n_dollars(old_str);
	to_expand = get_var_names(old_str, n);
	get_var_values(to_expand, env, e_code);
	new_str = build_str(old_str, to_expand);
	// print_expansion(to_expand); // remove
	// ft_printf("\033[34mold_str: [%s]\033[0m --> ", old_str);
	// if (new_str)
	// 	ft_printf("\033[35m[%s]\033[0m\n", new_str);
	// else
	// 	ft_printf("\033[35m[<null>]\033[0m\n");
	ft_lstclear(&to_expand, del_to_expand);
	free(old_str);
	return (new_str);
}

/*
	Iterate through the args and redirections od t_cmd structure, checking
	if there issomething to expand. In case of here_doc, the variable is not
	expanded!
*/
static int	check_expansion(t_cmd *cmd, t_list *env, int e_code)
{
	int				i;
	t_list			*redir;
	t_redir_data	*redir_content;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			if (ft_strchr(cmd->args[i], '$') && cmd->args[i][0] != TKN_S_QUOTE)
			{
				cmd->args[i] = expand(cmd->args[i], env, e_code);
				if (cmd->args[i] == NULL)
				{
					// custom error
				}
			}
			i++;
		}
	}
	redir = (t_list *)cmd->redir;
	while (redir)
	{
		redir_content = (t_redir_data *)redir->content;
		if (redir && redir_content->type != REDIR_HERE_DOC)
		{
			if (ft_strchr(redir_content->file_name, '$') && redir_content->file_name[0] != TKN_S_QUOTE)
				redir_content->file_name = expand(redir_content->file_name, env, e_code);
		}
		redir = redir->next;
	}
	return (0);
}

void	expansion(t_node *tree, t_list *env, int e_code)
{
	t_pipe	*pipe;
	t_cmd	*cmd;

	while (tree->type == IS_PIPE)
	{
		pipe = (t_pipe *)tree->content;
		cmd = (t_cmd *)pipe->left->content;
		check_expansion(cmd, env, e_code);
		tree = pipe->right;
	}
	cmd = (t_cmd *)tree->content; // check last one OOORRR the only-one
	check_expansion(cmd, env, e_code);
}
