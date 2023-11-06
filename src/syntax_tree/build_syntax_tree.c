/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_syntax_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:32:21 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/06 16:55:05 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tkn_data	*cpy_tkn_content(t_tkn_data *content)
{
	t_tkn_data	*cpy;

	cpy = ft_calloc(1, sizeof(t_tkn_data)); // prtct
	cpy->list_size = content->list_size;
	cpy->quote = content->quote;
	cpy->quote_status = content->quote_status;
	cpy->str = ft_strdup(content->str);
	cpy->type = content->type;
	cpy->white_space = content->white_space;
	return (cpy);
}

/*
	The tokens are divided into blocks.	Block means a set of tokens seaprated
	by the pipes, like the folowing: [ BLOCK_1 ] | [ BLOCK_2 ] | [ BLOCK_3 ]
*/
static t_list	*copy_tokens_block(t_list *tokens, t_node *node_c)
{
	t_tkn_data	*tkn_content;
	t_tkn_data	*tkn_content_cpy;
	t_list		*tkn_node_cpy;

	tkn_node_cpy = NULL;
	tkn_content_cpy = NULL;
	while (tokens) //tkn_content->type != '|' check after
	{
		tkn_content = (t_tkn_data *)tokens->content;
		if (ft_strncmp(tkn_content->str, "|", 1) == 0)
			return (tokens);
		tkn_content_cpy = cpy_tkn_content(tkn_content); // protect
		tkn_node_cpy = ft_lstnew(tkn_content_cpy); // protect
		if (!tkn_node_cpy)
			return (NULL);
		ft_lstadd_back(&((t_cmd *)node_c->content)->block, tkn_node_cpy);
		if (tokens->next)
			tokens = tokens->next;
		else
			break ;
	}
	return (tokens);
}

static t_node	*init_node_p(int n)
{
	t_node	*node_p;

	node_p = ft_calloc(1, sizeof(t_node)); // protect
	if (!node_p)
		return (NULL);
	node_p->type = IS_PIPE;
	node_p->n = n + 1;
	node_p->content = ft_calloc(1, sizeof(t_pipe)); // prtct
	if (!node_p->content)
	{
		// free(node_p);
		return (NULL);
	}
	((t_pipe *)node_p->content)->left = NULL;
	((t_pipe *)node_p->content)->right = NULL;
	return (node_p);
}

static t_node	*init_node_c(int n)
{
	t_node	*node_c;
	t_cmd	*cmd;

	node_c = ft_calloc (1, sizeof(t_node)); // prtct
	if (!node_c)
		return (NULL);
	node_c->type = IS_CMD;
	node_c->n = n;
	node_c->content = ft_calloc(1, sizeof(t_cmd)); // prtct
	if (!node_c->content)
	{
		// free(node_c);
		return (NULL);
	}
	cmd = (t_cmd *)node_c->content;
	cmd->block = NULL;
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	return (node_c);
}


/*
	@param n - just a number to identify which node of the tree it is
	and better visualize it when printed.
*/
t_node	*build_syntax_tree(t_list *tokens, int n)
{
	t_node		*node_c;
	t_node		*node_p;


	node_c = init_node_c(n);
	if (!node_c)
		return (NULL);	// free stuff


	tokens = copy_tokens_block(tokens, node_c);
	if (!tokens)
		return (NULL);	// free stuff


	node_p = NULL;
	if (ft_strncmp(((t_tkn_data *)tokens->content)->str, "|", 1) == 0)
	{
		ft_printf("_Create a pipe\n");
		tokens = tokens->next;
		node_p = init_node_p(n);
		if (!node_p)
		{
			//free node_c / free tokens
			return (NULL);
		}
		((t_pipe *)node_p->content)->left = node_c;
		((t_pipe *)node_p->content)->right = build_syntax_tree(tokens, n + 2);
		if (!((t_pipe *)node_p->content)->right)
		{
			//free node_c / free tokens // free_p
			return (NULL); // free current t_node
		}
		return (node_p);
	}
	// if (node_p)
	// {
	// 	ft_printf("returned a PIPE\n");
	// }
	// ft_printf("returned a NODE\n");
	return (node_c);
}














	// t_node		*node_c;
	// t_node		*node_p;


	// node_c = init_node_c(n);
	// if (!node_c)
	// 	return (NULL);	// free stuff


	// tokens = copy_tokens_block(tokens, node_c);
	// if (!tokens)
	// 	return (NULL);	// free stuff

	// node_p = NULL;
	// print_tokens(tokens);
	// if (tokens->next)
	// {
	// 	node_p = init_node_p(n);
	// 	if (!node_p)
	// 	{
	// 		//free node_c / free tokens
	// 		return (NULL);
	// 	}
	// 	((t_pipe *)node_p->content)->left = node_c;
	// 	((t_pipe *)node_p->content)->right = build_syntax_tree(tokens, n + 2);
	// 	if (!((t_pipe *)node_p->content)->right)
	// 	{
	// 		//free node_c / free tokens // free_p
	// 		return (NULL); // free current t_node
	// 	}
	// }
	// if (node_p)
	// 	return (node_p);
	// return (node_c);
