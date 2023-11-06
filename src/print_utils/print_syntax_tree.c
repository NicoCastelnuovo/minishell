/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:30:02 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/06 10:50:47 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_tree(t_node *tree)
{
	t_pipe	*pipe;
	t_list	*tokens;

	ft_printf("\n___ SYNTAX TREE ___\n\n");
	if (tree->type == IS_CMD)
	{
		tokens = ((t_cmd *)tree->content)->tokens;
		ft_printf("[cmd][%d]   ", tree->n);
		print_tokens(tokens);
		ft_printf("\n");
		return ;
	}
	while (tree->type == IS_PIPE)
	{
		pipe = (t_pipe *)tree->content;
		if (pipe->right->type == IS_PIPE)
		{
			tokens = ((t_cmd *)pipe->left->content)->tokens;
			ft_printf("[pipe][%d] ------> [cmd][%d]   ", tree->n, pipe->right->n);
			print_tokens(tokens);
			ft_printf("\n  |\n  |\n  |\n");
			tree = ((t_pipe *)tree->content)->right;
		}
		else
		{
			tokens = ((t_cmd *)pipe->left->content)->tokens;
			ft_printf("[pipe][%d] ------> [cmd][%d]   ", tree->n, pipe->right->n);
			print_tokens(tokens);
			ft_printf("\n  |\n  |\n  |\n");
			ft_printf("   --------------> [cmd][%d]   ", pipe->left->n);
			tokens = ((t_cmd *)pipe->right->content)->tokens;
			print_tokens(tokens);
			ft_printf("\n");
			break ;
		}
	}
	ft_printf("\n");
}
