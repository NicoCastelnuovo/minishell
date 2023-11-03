/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:30:02 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/03 15:31:35 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tkn_sublist(t_list *tkn_sublist)
{
	char	*s;

	ft_printf("[");
	while (tkn_sublist)
	{
		s = ((t_tkn_data *)tkn_sublist->content)->str;
		ft_printf("%s•", s);
		tkn_sublist = tkn_sublist->next;
	}
	ft_printf("]");
}

void	print_syntax_tree(t_node *root)
{
	t_pipe	*pipe;
	t_list	*tkn_sublist;

	ft_printf("\n");
	while (root->type == IS_PIPE)
	{
		pipe = (t_pipe *)root->content;
		if (pipe->right->type == IS_PIPE)
		{
			tkn_sublist = ((t_cmd *)pipe->left->content)->tkn_sublist;
			ft_printf("[pipe][%d] ------> [cmd][%d] ", root->n, pipe->right->n);
			print_tkn_sublist(tkn_sublist);
			ft_printf("\n  |\n  |\n  |\n");
			root = ((t_pipe *)root->content)->right;
		}
		else
		{
			tkn_sublist = ((t_cmd *)pipe->left->content)->tkn_sublist;
			ft_printf("[pipe][%d] ------> [cmd][%d] ", root->n, pipe->right->n);
			print_tkn_sublist(tkn_sublist);
			ft_printf("\n  |\n  |\n  |\n");
			ft_printf("   --------------> [cmd][%d] ", pipe->left->n);
			tkn_sublist = ((t_cmd *)pipe->right->content)->tkn_sublist;
			print_tkn_sublist(tkn_sublist);
			ft_printf("\n");
			break ;
		}
	}
	ft_printf("\n");
}
