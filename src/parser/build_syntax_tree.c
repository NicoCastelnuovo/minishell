/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_syntax_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:32:21 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/08 13:51:27 by ncasteln         ###   ########.fr       */
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
static t_list	*copy_tokens_block(t_list *curr_tkn, t_node *node_c)
{
	t_tkn_data	*tkn_content;
	t_tkn_data	*tkn_content_cpy;
	t_list		*tkn_node_cpy;
	t_list		*prev_tkn;

	tkn_node_cpy = NULL;
	tkn_content_cpy = NULL;
	prev_tkn = NULL;
	while (curr_tkn) // !!!!  After distributing in each filed the tokens, block could be deleted....
	{
		tkn_content = (t_tkn_data *)curr_tkn->content;
		if (((t_tkn_data *)curr_tkn->content)->type == TKN_PIPE)
			return (curr_tkn);
		tkn_content_cpy = cpy_tkn_content(tkn_content); // protect
		tkn_node_cpy = ft_lstnew(tkn_content_cpy); // protect
		if (!tkn_node_cpy)
			return (NULL);
		ft_lstadd_back(&((t_cmd *)node_c->content)->block, tkn_node_cpy);



		// first iter, prev_token doesn't exist
		if (prev_tkn)
			ft_printf("\x1b[32mprev[%s] <-- ", ((t_tkn_data*)prev_tkn->content)->str);
		else
			ft_printf("\x1b[32mprev(null) <-- ");
		ft_printf("curr[%s]", ((t_tkn_data*)curr_tkn->content)->str);
		if (curr_tkn->next)
			ft_printf(" --> next[%s]\x1b[0m", ((t_tkn_data*)curr_tkn->next->content)->str);
		else
			ft_printf(" --> next(null)\x1b[0m");
		ft_printf("\n");




		update_cmd_node(curr_tkn, prev_tkn, node_c); // make this jump 1 place if needed
		ft_printf("\n");
		prev_tkn = curr_tkn;
		if (curr_tkn->next)
			curr_tkn = curr_tkn->next;
		else
			break ;
	}
	return (curr_tkn);
}

static t_node	*init_pipe_node(int n)
{
	t_node	*node_p;

	node_p = ft_calloc(1, sizeof(t_node)); // protect
	if (!node_p)
		return (NULL);
	node_p->type = IS_PIPE;
	node_p->n = n + 1;
	node_p->content = ft_calloc(1, sizeof(t_pipe)); // prtct
	if (!node_p->content)
		return (free(node_p), NULL);
	((t_pipe *)node_p->content)->left = NULL;
	((t_pipe *)node_p->content)->right = NULL;
	return (node_p);
}

static t_node	*init_cmd_node(int n)
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
		return (free(node_c), NULL);
	cmd = (t_cmd *)node_c->content;
	cmd->block = NULL;
	cmd->args = NULL;
	cmd->redir = NULL; // proctect // modifed
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	return (node_c);
}

/*
	@param n - just a number to identify which node of the tree it is
	and visualize it when printed.
*/
t_node	*build_syntax_tree(t_list *tokens, int n)
{
	t_node		*node_c;
	t_node		*node_p;

	node_c = init_cmd_node(n);
	if (!node_c)
		return (NULL);
	tokens = copy_tokens_block(tokens, node_c);
	ft_printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
	node_p = NULL;
	if (ft_strncmp(((t_tkn_data *)tokens->content)->str, "|", 1) == 0)
	{
		tokens = tokens->next; // this line skips the pipe, which is not stored
		node_p = init_pipe_node(n);
		if (!node_p)
		{
			free_cmd_node(node_c);
			free_pipe_node(node_p);
			return (NULL);
		}
		((t_pipe *)node_p->content)->left = node_c;
		((t_pipe *)node_p->content)->right = build_syntax_tree(tokens, n + 2);
		if (!((t_pipe *)node_p->content)->right)
		{
			free_cmd_node(node_c);
			free_pipe_node(node_p);
			return (NULL);
		}
		return (node_p);
	}
	return (node_c);
}
