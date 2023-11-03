/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:32:21 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/03 09:33:28 by ncasteln         ###   ########.fr       */
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
static int	*parse_single_tkn(t_list *token)
{
	t_tkn_data	*tkn_data;

	tkn_data = ((t_tkn_data *)token->content);
	if (!token->next)
	{
		ft_printf("PARSE: [%s] (last)\n", tkn_data->str);
		return (0);
	}
	ft_printf("PARSE: [%s]\n", tkn_data->str);
	if (is_redirection(tkn_data->type))
	{
		ft_printf("	[R]\n");
		// check REDIRECTIONS sytax errors
		// if (!ok) return (0);
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
// ATTENTION !!!
//	- Im'm moving the tkn_list pointer
//	- Need to separate the functions AN maintain the move of tkn_list
//	- [MAYBE] --- create cmd and assign, after creation, to node_c->content
// create cmd
t_node	*build_syntax_tree(t_list *tkn_list, int n)
{
	t_node		*node_c;
	t_tkn_data	*tkn_content;
	t_list		*tkn_sublist;
	t_node		*node_p;


	// init_node_c(&node_c);
	node_c = NULL;
	node_c = ft_calloc (1, sizeof(t_node)); // prtct
	node_c->type = IS_CMD;
	node_c->n = n;
	node_c->content = ft_calloc(1, sizeof(t_cmd)); // prtct



	tkn_content = (t_tkn_data *)tkn_list->content;
	while (tkn_list && tkn_content->type != '|')
	{
		tkn_content = (t_tkn_data *)tkn_list->content;
		tkn_sublist = ft_lstnew(tkn_content); // protect
		ft_lstadd_back(&((t_cmd *)node_c->content)->tkn_sublist, tkn_sublist);
		parse_single_tkn(tkn_list);
		if (tkn_list->next)
			tkn_list = tkn_list->next;
		else
			break ;
	}
	ft_printf("------------------------\n");



	// create pipe node
	node_p = NULL;
	if (tkn_list->next)
	{
		node_p = ft_calloc(1, sizeof(t_node)); // protect
		node_p->type = IS_PIPE;
		node_p->n = n + 1;
		node_p->content = ft_calloc(1, sizeof(t_pipe)); // prtct
		((t_pipe *)node_p->content)->left = node_c;
		((t_pipe *)node_p->content)->right = build_syntax_tree(tkn_list, n + 2);
	}

	// return correct node
	if (node_p)
		return (node_p);
	return (node_c);
}
