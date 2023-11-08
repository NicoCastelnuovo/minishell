/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:31:07 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/08 09:46:08 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
#include "lexer.h"
/*
	SYNTAX TREE
	The tree is composed by t_node items. Each t_node can be either of type
	IS_PIPE or IS_CMD, and consequently its content is either t_pipe or t_cmd.
*/
enum e_node
{
	IS_PIPE,
	IS_CMD
};

typedef struct s_node
{
	int			n;
	enum e_node	type;
	void		*content;
}	t_node;

/*
	t_pipe is the content of t_node, when its type is IS_PIPE.
	It holds just two address to 2 different t_node.
*/
typedef struct s_pipe
{
	struct s_node	*left;
	struct s_node	*right;
}	t_pipe;

/*
	t_cmd is the content of t_node in case its type is IS_CMD'
	It holds information about the tokens in a block delimited by start/end of
	the input, and by pipes.
	@param tkn_sublist - given an input of "ls -la | cat -eb >out1", the list is
	divided into [ls -la | ][cat -eb >out1]
*/
typedef struct s_cmd
{
	t_list		*block;
	char		**args;			// top cat -e ls      ftsplit("ls -la Makefile", ' ');
	t_list		*redir;			// in1(<) - out4(>) - temp1(<<) - temp2(<<) - temp3(<<) - (null or "")(>)
	int			fd_in;			// still necessary ???
	int			fd_out;
	int			err_code;
}	t_cmd;

enum e_redir
{
	REDIR_IN = '<',		// <
	REDIR_OUT = '>',	// >
	REDIR_HERE_DOC,		// <<
	REDIR_APPEND		// >>
};

typedef struct s_redir_data
{
	char			*file_name;
	enum e_redir	type;
}	t_redir_data;

// ---------------------------------------------------------------- SYNTAX TREE
t_node	*build_syntax_tree(t_list *token, int n);
void	free_tree(t_node *tree);
void	free_cmd_node(t_node *node_c);
void	free_pipe_node(t_node *node_p);
void	free_dptr(char **p);

// -------------------------------------------------------------------- PARSING
char	*parse(t_list *tkn);
int		is_redir(t_tkn_type tkn_type);

// ----------------------------------------------------------- UPDATE CMD TABLE
void	update_cmd_node(t_list *curr_tkn, t_list *prev_tkn, t_node *node);

// ---------------------------------------------------------------- PRINT UTILS
void	print_syntax_tree(t_node *root);
void	print_redir_list(t_list *redir);
void	print_args(char **args);

#endif
