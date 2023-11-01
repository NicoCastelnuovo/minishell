/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:04 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/01 12:28:53 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cc main.c -I./include/ -I./mylib/libft/ -I./mylib/ft_printf/ -I./mylib/get_next_line/ -L./mylib/ -lmylib


// int	main()
// {
// 	// <in1 cat -e | tail -3 | wc > out1 | cat -e
// 	t_node	*node1;
// 	t_node	*node2;
// 	t_node	*node3;

// 	node1 = malloc (sizeof(t_node));
// 	node1->type = IS_PIPE;
// 	node2 = malloc (sizeof(t_node));
// 	node2->type = IS_PIPE;
// 	node3 = malloc (sizeof(t_node));
// 	node3->type = IS_PIPE;

// 	// while the current pipe is not the last one
// 	node1->content->pipe->left = malloc(sizeof(t_node));
// 	node1->content->pipe->left->type = IS_CMD;
// 	// node1->content->pipe->left->content->cmd->block = <in1 cat -e
// 	node1->content->pipe->right = node2;


// 	node2->content->pipe->left = malloc(sizeof(t_node));
// 	node2->content->pipe->left->type = IS_CMD;
// 	// node1->content->pipe->left->content->cmd->block = tail -3
// 	node2->content->pipe->right = node3;


// 	node3->content->pipe->left = malloc(sizeof(t_node));
// 	node3->content->pipe->left->type = IS_CMD;
// 	// node1->content->pipe->left->content->cmd->block = wc > out1
// 	// IS THE LAST PIPE!
// 	node3->content->pipe->right = malloc(sizeof(t_node));
// 	node3->content->pipe->right->type = IS_CMD;
// 	// node1->content->pipe->left->content->cmd->block = cat -e


// 	return (0);
// }
