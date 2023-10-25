/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:44:50 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/25 10:17:23 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef enum	s_type
{
	WORD = 1,
	FILE_NAME = 2,
	ENV_VAR = 3,
	REDIRECT_OUT_CONCAT = 4,
	HERE_DOC = 5,
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	WHITESPACE = ' ',
	NEW_LINE = '\n',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"',
	ESCAPE_CHAR = '\\',
	PIPE = '|',
	DOLLAR_CHAR = '$',
}	t_type;



typedef struct	s_token
{
	int				length;
	int				type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct	s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}				t_dlist;

typedef struct	s_var
{
	char	*name;
	char	*value;
	int		name_len;
	int		value_len;
}			t_var;

#endif
