/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:53:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/08 09:10:40 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_cmd_redir(t_list *curr_tkn, t_list *prev_tkn, t_cmd *cmd)
{
	t_tkn_data		*next_content;
	t_tkn_data		*curr_content;
	t_redir_data	*new_content;
	t_list			*new_node;

	// first iteration ----- // move to initialization ???
	// if (!prev_tkn) // first iteration
	// {

	// }
	curr_content = (t_tkn_data *)curr_tkn->content;
	next_content = (t_tkn_data *)curr_tkn->next->content;

	new_content = ft_calloc(1, sizeof(t_redir_data)); // protect
	new_content->type = curr_content->type;
	new_content->file_name = ft_strdup(next_content->str);
	new_node = ft_lstnew(new_content); // protect

	ft_printf("	Added to t_list redir: filename[%s]", new_content->file_name);
	ft_lstadd_back(&cmd->redir, new_node);
}

static void	update_cmd_args(char *s, t_cmd *cmd)
{
	int		i;
	int		n_args;
	char	**new_args;

	if (!cmd->args) // first iteration ----- // move to initialization ???
	{
		cmd->args = ft_calloc(2, sizeof(char *)); // protect
		cmd->args[0] = ft_strdup(s); // protect
		cmd->args[1] = NULL; // protect
		return ;
	}
	n_args = 0;
	while (cmd->args[n_args])
		n_args++;
	ft_printf("	n_args = { %d }\n", n_args);
	new_args = ft_calloc(n_args + 2, sizeof(char *)); // protect
	i = 0;
	while (i < n_args)
	{
		new_args[i] = ft_strdup(cmd->args[i]);
		ft_printf("	new_args[i] %s\n", new_args[i]);
		i++;
	}
	new_args[i] = ft_strdup(s);
	new_args[i + 1] = NULL;
	free_dptr(cmd->args);
	cmd->args = new_args;
}

/*
	Take the current token assuming there is any syntax error, and assigns it
	to the current member of t_cmd data structure.
*/
t_list	*update_cmd_node(t_list *curr_tkn, t_list *prev_tkn, t_node *node)
{
	t_tkn_data	*curr_content;
	t_tkn_data	*prev_content;

	curr_content = NULL;
	prev_content = NULL;
	if (curr_tkn)
		curr_content = (t_tkn_data *)curr_tkn->content;
	if (!prev_tkn) // first iter
	{
		ft_printf("	No prev: curr_tkn [%s]\n", curr_content->str);
		if (is_redir(curr_content->type)) // in this case, curr_tkn is moved foreward
		{
			update_cmd_redir(curr_tkn, prev_tkn, node->content);
			return (curr_tkn->next);
		}
		// if (curr_content->type == TKN_WORD)
		// 	update_cmd_args(curr_content->str, node->content);
	}
	else
	{
		prev_content = (t_tkn_data *)prev_tkn->content;
		ft_printf("	Check curr_tkn[%s] with prev_tkn[%s]\n", curr_content->str, prev_content->str);
		if (is_redir(curr_content->type))
		{
			update_cmd_redir(curr_tkn, prev_tkn, node->content);
			return (curr_tkn->next);
		}
		// if (curr_content->type == TKN_WORD)
		// 	update_cmd_args(curr_content->str, node->content);
	}
	return (curr_tkn);
}
