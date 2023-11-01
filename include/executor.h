/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:08:21 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/01 10:15:56 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef enum redirect
{
	IN,			// <
	OUT,		// >
	HERE_DOC,	// <<
	APPEND		// >>
}	t_redirect;

typedef struct s_file
{
	char		*name;
	t_redirect	type;
	t_file		*next;
}	t_file;

typedef struct s_pipe
{
	t_tree_node	*left;
	t_tree_node	*right;
}	t_pipe;

typedef struct s_cmd
{
	char	*name;		// cat
	char	**args;		// top cat -e ls
	t_file	*in_out;	// in1(<) - out4(>) - temp1(<<) - temp2(<<) - temp3(<<) - (null or "")(>)
	int		fd_in; 		// still necessary
	int		fd_out;
}	t_cmd;

typedef union u_tree_node
{
	t_pipe	pipe;
	t_cmd	cmd;
}	t_tree_node;

#endif
