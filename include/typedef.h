/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:44:50 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/17 15:09:39 by fahmadia         ###   ########.fr       */
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

#endif
