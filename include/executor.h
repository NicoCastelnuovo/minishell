/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:08:21 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/01 12:11:38 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

// TREE NODES DEFINITIONS
enum e_node
{
	IS_PIPE,
	IS_CMD
};

union u_content
{
	struct s_pipe	*pipe;
	struct s_cmd	*cmd;
};

typedef struct s_node
{
	enum e_node		type;
	union u_content	*content;
}	t_node;


// TYPE PIPE
typedef struct s_pipe
{
	struct s_node	*left;
	struct s_node	*right;
}	t_pipe;


// TYPE CMD
enum e_redir
{
	IN,			// <
	OUT,		// >
	HERE_DOC,	// <<
	APPEND		// >>
};

typedef struct s_redir
{
	char			*name;
	enum e_redir	type;
	struct s_redir	*next;
}	t_file;

typedef struct s_cmd
{
	char			*block;		// <in1 cat -e
	char			*name;		// cat
	char			**args;		// top cat -e ls
	struct s_redir	*in_out;	// in1(<) - out4(>) - temp1(<<) - temp2(<<) - temp3(<<) - (null or "")(>)
	int				fd_in; 		// still necessary ???
	int				fd_out;
}	t_cmd;


#endif
