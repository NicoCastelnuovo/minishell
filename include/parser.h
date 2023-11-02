/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:31:07 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/02 16:53:21 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// TREE NODES DEFINITIONS
enum e_node
{
	IS_PIPE,
	IS_CMD
};

typedef struct s_node
{
	int			n;
	void		*content;
	enum e_node	type;
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
	IS_IN,			// <
	IS_OUT,			// >
	IS_HERE_DOC,	// <<
	IS_APPEND		// >>
};

typedef struct s_redir
{
	char			*name;
	enum e_redir	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	t_list			*block;		// NO NEEDED at the end probably
	char			*name;		// cat
	char			**args;		// top cat -e ls
	struct s_redir	*file;	// in1(<) - out4(>) - temp1(<<) - temp2(<<) - temp3(<<) - (null or "")(>)
	int				fd_in; 		// still necessary ???
	int				fd_out;
}	t_cmd;

t_node	*build_syntax_tree(t_list *token, int n);
void	print_block(t_list *block);
void	print_syntax_tree(t_node *root);


#endif
