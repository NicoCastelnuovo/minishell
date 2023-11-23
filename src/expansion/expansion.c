/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:18:55 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/23 12:48:09 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	For each variable name in the list, get_env_custom() is applied, and the value is
	duplicated into the node. If the variable doesn't exist, an empty string
	is duplicated.
*/
static int	get_var_values(t_list *var_to_expand, t_list *env, int e_code)
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
		if (!expanded)
			return (ft_lstclear(&var_to_expand, del_to_expand), 1);
		var->value = expanded;
		var->value_len = ft_strlen(var->value);
		var_to_expand = var_to_expand->next;
	}
	return (0);
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
		new_node = ft_lstnew(var);
		if (!new_node)
			return (ft_lstclear(&var_to_expand, del_to_expand), NULL);
		ft_lstadd_back(&var_to_expand, new_node);
		i++;
	}
	return (var_to_expand);
}

static int	*get_first_var_name(char *s) // like $USERabcd or $USER+abcd or $SHIT!!!
{
	int	i;
	char	*var_name;

	i = 1;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	var_name = ft_calloc(i + 1, sizeof(char)); // protect
	ft_strlcpy(var_name, s + 1, i);
	return (var_name);
}

static int	*get_first_var_name_len(char *s) // like $USERabcd or $USER+abcd or $SHIT!!!
{
	int	len;

	len = 1; // starts from the second position
	while (s[len] && (ft_isalnum(s[len]) || s[len] == '_'))
		len++;
	return (len); // no counts also dollar because already does in i++
}

/*
	Trying to calculate the length of a new expanded string
*/
char	*expand(char *old_str, t_list *env, int e_code)
{
	int		i;
	char	*dollar;
	char	*new_str;
	int		len;
	char	kind_of;
	int		open;
	char	*var_name;
	int		var_name_len;
	char	*var_value;
	int		var_value_len;

	i = 0;
	len = 0;
	kind_of = -1;
	open = 0;
	var_name = NULL;
	var_name_len = 0;
	var_value = NULL;
	var_value_len = 0;
	// get total length ???
	while (old_str[i]) // abc"$USER'hello'"ok
	{
		if (old_str[i] == '$') // len depends
		{
			if (old_str[i + 1] == '$') //$$$$$ just print it
			{
				ft_printf("Checked a $...\n");
				len++;
			}
			else if (old_str[i + 1] == '?') //$?$?$?$? ---- how much ?
			{
				len += ft_strlen(ft_itoa(e_code)); // allocates
			}
			else if (old_str[i + 1] == TKN_S_QUOTE) // $'"example $USER no expand"'
			{
				// not count the dollar
				// it will be removed but the quotes remain!
			}
			else if (old_str[i + 1] == TKN_D_QUOTE) // $"'example $USER to expand'"
			{
				// not count the dollar
				// it will be removed but the quotes remain!
			}
			else // $U
			{
				var_name = get_first_var_name(old_str + i); //allocates
				var_name_len = ft_strlen(var_name);
				var_value = get_env_custom(var_name, env);
				if (var_value)
					var_value_len = ft_strlen(var_value);
				len += var_value_len;
				i += var_name_len;
			}
		}
		else
		{
			if (old_str[i] == TKN_S_QUOTE)
			{
				if (!open)
				{
					open = 1;
					kind_of = TKN_S_QUOTE;
				}
				else
				{
					if (kind_of == TKN_S_QUOTE)
					{
						open = 0;
						kind_of = -1;
					}
				}
				len++;
			}
			else if (old_str[i] == TKN_D_QUOTE)
			{
				if (!open)
				{
					open = 1;
					kind_of = TKN_D_QUOTE;
				}
				else
				{
					if (kind_of == TKN_D_QUOTE)
					{
						open = 0;
						kind_of = -1;
					}
				}
				len++;
			}
			else
				len++;
		}
		i++;
	}
	ft_printf("Total len = [%d]\n", len);
	exit(1);
}

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
		if (check_expansion(cmd, data->env, data->e_code))
		{
			data->e_code = 1;
			return ;
		}
		node = pipe->right;
	}
	cmd = (t_cmd *)node->content;
	if (check_expansion(cmd, data->env, data->e_code))
	{
		data->e_code = 1;
		return ;
	}
}





// /*
// 	For each variable name in the list, get_env_custom() is applied, and the value is
// 	duplicated into the node. If the variable doesn't exist, an empty string
// 	is duplicated.
// */
// static int	get_var_values(t_list *var_to_expand, t_list *env, int e_code)
// {
// 	char	*expanded;
// 	t_var	*var;

// 	expanded = NULL;
// 	while (var_to_expand)
// 	{
// 		var = (t_var *)var_to_expand->content;
// 		if (var->name_len == 0)
// 			expanded = ft_strdup("$");
// 		else if (var->name[0] == '?' && var->name_len == 1)
// 			expanded = ft_itoa(e_code);
// 		else if (get_env_custom(var->name, env))
// 			expanded = ft_strdup(get_env_custom(var->name, env));
// 		else
// 			expanded = ft_strdup("");
// 		if (!expanded)
// 			return (ft_lstclear(&var_to_expand, del_to_expand), 1);
// 		var->value = expanded;
// 		var->value_len = ft_strlen(var->value);
// 		var_to_expand = var_to_expand->next;
// 	}
// 	return (0);
// }

// static t_list	*get_var_names(char *s, int n)
// {
// 	t_list	*var_to_expand;
// 	t_list	*new_node;
// 	t_var	*var;
// 	int		i;

// 	var_to_expand = NULL;
// 	i = 0;
// 	while (i < n)
// 	{
// 		var = ft_calloc(1, sizeof(t_var));
// 		if (!var)
// 			return (ft_lstclear(&var_to_expand, del_to_expand), NULL);
// 		s = ft_strchr(s, '$');
// 		s++;
// 		var->name_len = get_var_name_len(s);
// 		if (var->name_len == 0)
// 			var->name = ft_strdup("$");
// 		else
// 			var->name = ft_substr(s, 0, var->name_len);
// 		if (!var->name)
// 			return (ft_lstclear(&var_to_expand, del_to_expand), NULL);
// 		var->value = NULL;
// 		var->value_len = -1;
// 		new_node = ft_lstnew(var);
// 		if (!new_node)
// 			return (ft_lstclear(&var_to_expand, del_to_expand), NULL);
// 		ft_lstadd_back(&var_to_expand, new_node);
// 		i++;
// 	}
// 	return (var_to_expand);
// }

// /*
// 	How expansion is performed:
// 		• get n of pssible expansion to perform ("$$$" are still counted
// 		as three potential expansion to be done);
// 		• extract the variable names ("$" is considered a variable name),
// 		• get the variable values and build the new string which will
// 		replace the origial one.
// 	In each step, if something goes wrong, the operation is stopped, and
// 	the expansion is not performed.
// */
// char	*expand(char *old_str, t_list *env, int e_code)
// {
// 	int		n;
// 	t_list	*to_expand;
// 	char	*new_str;

// 	n = get_n_dollars(old_str); // $"Hello world USER $USER"
// 	to_expand = get_var_names(old_str, n);
// 	if (!to_expand)
// 		return (NULL);
// 	if (get_var_values(to_expand, env, e_code))
// 		return (NULL);
// 	new_str = build_str(old_str, to_expand);
// 	ft_lstclear(&to_expand, del_to_expand);
// 	if (!new_str)	// means: if something failed building the newstr, the old one is not replaced !!!
// 		return (free(new_str), old_str);
// 	return (free(old_str), new_str);
// }

// void	expansion(t_data *data)
// {
// 	t_node	*node;
// 	t_pipe	*pipe;
// 	t_cmd	*cmd;

// 	if (!data->tree || data->e_code)
// 		return ;
// 	node = data->tree;
// 	while (node->type == IS_PIPE)
// 	{
// 		pipe = (t_pipe *)node->content;
// 		cmd = (t_cmd *)pipe->left->content;
// 		if (check_expansion(cmd, data->env, data->e_code))
// 		{
// 			data->e_code = 1;
// 			return ;
// 		}
// 		node = pipe->right;
// 	}
// 	cmd = (t_cmd *)node->content;
// 	if (check_expansion(cmd, data->env, data->e_code))
// 	{
// 		data->e_code = 1;
// 		return ;
// 	}
// }

// /*
// 	Think about expansion not for just a variable but also for phrases
// 	and long strings
// */
