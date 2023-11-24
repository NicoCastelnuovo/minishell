/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:18:55 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/24 15:32:26 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	is_open = -1;

	var_to_expand = NULL;
	i = 0;
	while (i < n) /// includes stuff not to expand
	{
		while (*s != '$')
		{
			if (*s == TKN_S_QUOTE || *s == TKN_D_QUOTE)
				change_is_open_quote(*s, &is_open, NULL);
			s++;
		}
		// here is $
		// s = ft_strchr(s, '$');
		s++;
		if (is_open == TKN_S_QUOTE)
		{
			i++;
			continue ;
		}
		var = ft_calloc(1, sizeof(t_var));
		if (!var)
			return (ft_lstclear(&var_to_expand, del_to_expand), NULL);
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
char	*expand(char *old_str, t_data *data)
{
	int		n;
	t_list	*to_expand;
	char	*mid_str;
	char	*new_str;

	mid_str = mid_step(old_str);
	if (!mid_str)
		return (NULL);
	n = get_n_dollars(mid_str);
	to_expand = get_var_names(mid_str, n);
	get_var_values(to_expand, data->env, data->e_code);
	new_str = build_str(mid_str, to_expand);
	ft_lstclear(&to_expand, del_to_expand);
	free(mid_str);
	return (new_str);
}

static int	redir_expansion(t_cmd *cmd, t_data *data)
{
	t_list			*redir;
	t_redir_data	*redir_content;
	char			*tmp;

	redir = (t_list *)cmd->redir;
	redir_content = NULL;
	tmp = NULL;
	while (redir)
	{
		redir_content = (t_redir_data *)redir->content;
		if (redir && redir_content->type != REDIR_HERE_DOC) // make it later because of expansion inside
		{
			if (ft_strchr(redir_content->file_name, '$'))
			{
				tmp = redir_content->file_name;
				redir_content->file_name = expand(redir_content->file_name, data);
				free(tmp);
				if (!redir_content->file_name)
					return (error(redir_content->file_name, NULL, CE_EXPANSION), 1);
			}
		}
		redir = redir->next;
	}
	return (0);
}

static int	args_expansion(t_cmd *cmd, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			if (ft_strchr(cmd->args[i], '$'))
			{
				tmp = cmd->args[i];
				cmd->args[i] = expand(cmd->args[i], data);
				free(tmp);
				if (cmd->args[i] == NULL)
					return (error(cmd->args[i], NULL, CE_EXPANSION), 1);
			}
			i++;
		}
	}
	return (0);
}

static int	check_expansion(t_cmd *cmd, t_data *data)
{
	if (args_expansion(cmd, data))
		return (1);
	if (redir_expansion(cmd, data))
		return (1);
	return (0);
}

/*
	The expander perform the following operations:
		• Expands only args and redir which are not HERE_DOC
		• Removes the $ from the string, like $"..." or $'...'
		• Iterate through the string and counts ALL remaining $
		• Iterate another time and switches the open/close single/double quotes
			so that the expansion is performed or not
		• If the most external quotes are not single, the expansion is done
		• After the expansion, the quote_removal() function is called to
			remove the remaining unuseful quotes
*/
void	expansion(t_data *data)
{
	t_node	*node;
	t_pipe	*pipe;
	t_cmd	*cmd;

	if (!data->tree || data->e_code)
		return ;
	node = data->tree;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		cmd = (t_cmd *)pipe->left->content;
		if (check_expansion(cmd, data))
		{
			data->e_code = 1;
			return ;
		}
		node = pipe->right;
	}
	cmd = (t_cmd *)node->content;
	if (check_expansion(cmd, data))
	{
		data->e_code = 1;
		return ;
	}
}
