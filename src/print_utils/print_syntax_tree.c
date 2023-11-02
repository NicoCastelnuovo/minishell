/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:30:02 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/02 10:53:48 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_block(t_list *block)
{
	ft_printf("[");
	while (block)
	{
		ft_printf("%s ", (char *)block->content);
		block = block->next;
	}
	ft_printf("]\n");
}

void	print_syntax_tree(t_node *root)
{
	t_pipe	*pipe;
	t_list	*block;

	while (root->type == IS_PIPE)
	{
		pipe = (t_pipe *)root->content;
		block = ((t_cmd *)pipe->left->content)->block;
		ft_printf("CMD [%d] ", pipe->left->n);
		print_block(block);
		ft_printf("	/\\	\n");
		ft_printf("	|	\n");
		ft_printf("	|	\n");
		ft_printf("     PIPE[%d]\n", root->n);
		ft_printf("	|	\n");
		ft_printf("	|	\n");
		ft_printf("	\\/	\n");
		if (pipe->right->type == IS_PIPE)
			root = pipe->right;
		else
		{
			ft_printf("CMD[%d] ", ((t_pipe *)root->content)->right->n);
			print_block(block);
			break ;
		}
	}
}
