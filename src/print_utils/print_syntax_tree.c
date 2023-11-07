/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:30:02 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/06 16:16:58 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_tree(t_node *tree)
{
	t_pipe	*pipe;
	t_list	*tokens;

	ft_printf("\n____SYNTAX TREE____");
	if (!tree)
		return ;
	if (tree->type == IS_CMD)
	{
		ft_printf("___First node is CMD___\n\n");
		tokens = ((t_cmd *)tree->content)->block;
		ft_printf("[cmd][%d]   ", tree->n);
		print_tokens(tokens);
		ft_printf("\n");
		return ;
	}
	ft_printf("___First node is PIPE___\n\n");
	while (tree->type == IS_PIPE)
	{
		pipe = (t_pipe *)tree->content;
		if (pipe->right->type == IS_PIPE)
		{
			tokens = ((t_cmd *)pipe->left->content)->block;
			ft_printf("[pipe][%d] ------> [cmd][%d]   ", tree->n, pipe->left->n);
			print_tokens(tokens);
			ft_printf("  |\n  |\n  |\n");
			tree = ((t_pipe *)tree->content)->right;
		}
		else
		{
			tokens = ((t_cmd *)pipe->left->content)->block;
			ft_printf("[pipe][%d] ------> [cmd][%d]   ", tree->n, pipe->left->n);
			print_tokens(tokens);
			ft_printf("  |\n  |\n  |\n");
			ft_printf("   -------------> [cmd][%d]   ", pipe->right->n);
			tokens = ((t_cmd *)pipe->right->content)->block;
			print_tokens(tokens);
			ft_printf("\n");
			break ;
		}
	}
	ft_printf("\n");
}