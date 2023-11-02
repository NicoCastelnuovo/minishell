/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:30:02 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/02 15:14:28 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_block(t_list *block)
{
	ft_printf("[");
	while (block)
	{
		ft_printf("%s•", (char *)block->content);
		block = block->next;
	}
	ft_printf("]");
}

void	print_syntax_tree(t_node *root)
{
	t_pipe	*pipe;
	t_list	*block;

	ft_printf("\n");
	while (root->type == IS_PIPE)
	{
		pipe = (t_pipe *)root->content;
		if (pipe->right->type == IS_PIPE)
		{
			block = ((t_cmd *)pipe->left->content)->block;
			ft_printf("[pipe][%d] ------> [cmd][%d] ", root->n, pipe->right->n);
			print_block(block);
			ft_printf("\n  |\n  |\n  |\n");
			root = ((t_pipe *)root->content)->right;
		}
		else
		{
			block = ((t_cmd *)pipe->left->content)->block;
			ft_printf("[pipe][%d] ------> [cmd][%d] ", root->n, pipe->right->n);
			print_block(block);
			ft_printf("\n  |\n  |\n  |\n");
			ft_printf("   -------------> [cmd][%d] ", pipe->left->n);
			block = ((t_cmd *)pipe->right->content)->block;
			print_block(block);
			ft_printf("\n");
			break ;
		}
	}
	ft_printf("\n");
}
