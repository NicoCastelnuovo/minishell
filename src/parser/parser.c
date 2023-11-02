/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:32:21 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/02 16:20:51 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	REDIRECT_OUT_CONCAT = 7,
	HERE_DOC = 8,
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
*/
static int	is_redirection(int tkn_type)
{
	if (tkn_type == REDIRECT_OUT_CONCAT ||
		tkn_type == HERE_DOC ||
		tkn_type == REDIRECT_IN ||
		tkn_type == REDIRECT_OUT )
		return (1);
	return (0);
}

/*
	Process the token and its directly next one, checking for syntax errors.
	If everything is good, the node->content is populated with the t_cmd data.
*/
int		parse_single_tkn(t_list *token)
{
	t_tkn_data	*tkn_data;

	tkn_data = ((t_tkn_data *)token->content);
	if (!token->next)
	{
		// ony parse the current
		ft_printf("PARSE: [%s] (last)\n", tkn_data->str);
		return (0);
	}
	ft_printf("PARSE: [%s]\n", tkn_data->str);
	if (is_redirection(tkn_data->type))
	{
		// check REDIRECTIONS sytax errors
	}
	if (tkn_data->type == PIPE)
	{
		// check PIPES sytax errors
	}
	return (0);
}


/*
	@param n - just a number to identify which node of the tree it is
	and better visualize it when printed.
*/
t_node	*build_syntax_tree(t_list *tkn_list, int n)
{
	t_node		*pipe;
	t_node		*cmd;
	t_tkn_data	*tkn_content;
	t_list		*new_block_item;

	// ATTENTION !!!
	//	- Im'm moving the tkn_list pointer
	//	- Need to separate the functions AN maintain the move of tkn_list


	// create cmd
	cmd = NULL;
	cmd = ft_calloc (1, sizeof(t_node)); // prtct
	cmd->type = IS_CMD;
	cmd->n = n;
	cmd->content = ft_calloc(1, sizeof(t_cmd)); // prtct
	tkn_content = (t_tkn_data *)tkn_list->content;
	while (tkn_list && tkn_content->type != '|')
	{
		tkn_content = (t_tkn_data *)tkn_list->content;
		new_block_item = ft_lstnew(tkn_content->str); // protect --- // create block JUST to visualize
		ft_lstadd_back(&((t_cmd *)cmd->content)->block, new_block_item);
		parse_single_tkn(tkn_list);
		// check error
		if (tkn_list->next)
			tkn_list = tkn_list->next;
		else
			break ;
	}
	ft_printf("------------------------\n");



	// create pipe node
	pipe = NULL;
	if (tkn_list->next)
	{
		pipe = ft_calloc(1, sizeof(t_node)); // protect
		pipe->type = IS_PIPE;
		pipe->n = n + 1;
		pipe->content = ft_calloc(1, sizeof(t_pipe)); // prtct
		((t_pipe *)pipe->content)->left = cmd;
		((t_pipe *)pipe->content)->right = build_syntax_tree(tkn_list, n + 2);
	}

	// return correct node
	if (pipe)
		return (pipe);
	return (cmd);
}
