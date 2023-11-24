/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:18:55 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/24 13:15:24 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *original_str, t_data *data)
{
	char	*no_dollar;
	char	*e_code_expanded;
	char	*var_expanded;

	no_dollar = mid_step(original_str);
	e_code_expanded = expand_e_code(no_dollar, data->e_code);
	if (!e_code_expanded)
		return (NULL);
	exit(1);
	// new_str = get_expanded_str(old_str, total_new_len, data);
	// if (!new_str)
	// 	return (NULL);
	// return (var_expanded);
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

/*
	Iterate through the args and redirections od t_cmd structure, checking
	if there issomething to expand. In case of here_doc, the variable is not
	expanded!
*/
int	check_expansion(t_cmd *cmd, t_data *data)
{
	if (args_expansion(cmd, data))
		return (1);
	if (redir_expansion(cmd, data))
		return (1);
	return (0);
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

/*	to check
	hello$USER (13)
	hello'$USER' (12)
	hello"$USER" (15)
	hello"'$USER'" (17)
	hello'"$USER"' (14)
	hello$"'$USER'" (17)
	hello$'"$USER"' (14)
	hello$NOTHINGworld (10)
	hello$$$$$ (10)
	hello$?$?$?$?$? (10) if ecode == 0
	hello$?$USER$$$ (17) if ecode == 0
*/
