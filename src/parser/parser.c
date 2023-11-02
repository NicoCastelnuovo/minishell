/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:32:21 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/02 10:46:55 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_tokens(t_list *tokens) //remove
{
	t_list *temp = tokens;
	while (temp)
	{
		t_tkn_data *tkn_data = (t_tkn_data *)temp->content;
		if (tkn_data->type == 1)
			ft_printf("[%s]	type -> [%c]\n", tkn_data->str, 'w');
		else
			ft_printf("[%s]	type -> [%c]\n", tkn_data->str, tkn_data->type);
		temp = temp->next;
	}
}



t_node	*parse(t_list *token, int n)
{
	t_list		*block;
	t_node		*pipe;
	t_node		*cmd;
	t_tkn_data	*content;
	t_list		*new_block_item;

	// print_tokens(token);

	block = NULL;
	pipe = NULL;
	cmd = NULL;



	while (token->next && content->type != '|')
	{
		content = (t_tkn_data *)token->content;
		ft_printf("processing [%s]\n", content->str);
		new_block_item = ft_lstnew(content->str); // protect
		ft_lstadd_back(&block, new_block_item);
		token = token->next;
	}
	if (!token->next)
	{
		content = (t_tkn_data *)token->content;
		ft_printf("processing [%s]\n", content->str);
		new_block_item = ft_lstnew(content); // protect
		ft_lstadd_back(&block, new_block_item);
	}
	// check_block


	// create cmd
	cmd = ft_calloc (1, sizeof(t_node)); // prtct
	cmd->type = IS_CMD;
	cmd->n = n;
	cmd->content = ft_calloc(1, sizeof(t_cmd)); // prtct
	((t_cmd *)cmd->content)->block = block;


	// create pipe node
	if (token->next)
	{
		pipe = ft_calloc(1, sizeof(t_node)); // protect
		pipe->type = IS_PIPE;
		pipe->n = n + 1;
		pipe->content = ft_calloc(1, sizeof(t_pipe)); // prtct
		((t_pipe *)pipe->content)->left = cmd;
		((t_pipe *)pipe->content)->right = parse(token, n + 2);
	}

	ft_printf("Node [%d] is CMD\n", cmd->n);
	if (pipe)
		ft_printf("Node [%d] is PIPE\n", pipe->n);

	if (pipe)
		return (pipe);
	return (cmd);
}
