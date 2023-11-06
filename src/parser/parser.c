/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:06:20 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/06 14:20:34 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*parse_tkn(t_list *tokens)
{
	t_tkn_type	type;

	type = ((t_tkn_data *)tokens->content)->type;
	ft_printf("PARSE [%s]\n", ((t_tkn_data *)tokens->content)->str);
	if (is_redir(type))
	{

	}
	else if (type == TKN_PIPE)
	{

	}
	return (0);
}

static void	parse_node(t_cmd *cmd)
{
	while (cmd->block)
	{
		parse_tkn(cmd->block);
		cmd->block = cmd->block->next;
	}
}

void	parse(t_node *tree)
{
	t_pipe	*pipe;
	t_list	*tkn_sublist;
	t_cmd	*cmd;

	pipe = (t_pipe *)tree->content;
	while (pipe->right->type == IS_PIPE)
	{
		pipe = (t_pipe *)tree->content;
		parse_node(pipe->left->content);
		ft_printf("------------------------\n");
		tree = pipe->right;
	}
	parse_node(pipe->right->content);
	ft_printf("\n");
}





	// t_tkn_data	*tkn_curr;
	// t_tkn_data	*tkn_next;

	// tkn_curr = ((t_tkn_data *)(*tkn)->content);
	// if ((*tkn)->next)
	// {
	// 	tkn_next = ((t_tkn_data *)(*tkn)->next->content);
	// 	ft_printf("PARSE: [%s]\n", tkn_curr->str);
	// 	if (is_redir(tkn_curr->type))
	// 	{
	// 		cmd->err_code = is_redir_syntax_err(tkn_curr, tkn_next);
	// 		if (!cmd->err_code)
	// 		{
	// 			update_cmd_tab_redir_type(cmd, tkn_curr, tkn_next); // prtct
	// 			return (0);
	// 		}
	// 		else
	// 			return (1);
	// 	}
	// 	if (tkn_curr->type == TKN_FILE_NAME)
	// 	{
	// 		update_cmd_tab_redir_filename(cmd, tkn_curr);
	// 		return (0);
	// 	}
	// 	if (tkn_curr->type == TKN_WORD ||
	// 		tkn_curr->type == TKN_D_QUOTED_STR ||
	// 		tkn_curr->type == TKN_S_QUOTED_STR)
	// 	{
	// 		update_cmd_tab_args(cmd, tkn_curr);
	// 		return (0);
	// 	}
	// }
	// else // final tkn of the input
	// {
	// 	ft_printf("PARSE: [%s] (last)\n", tkn_curr->str);
	// 	return (0);
	// }
