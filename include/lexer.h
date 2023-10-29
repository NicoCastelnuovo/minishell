/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:44:50 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/29 11:11:52 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define SPECIAL_CHAR_NUM 10

typedef enum s_type
{
	WORD = 1,
	S_QUOTED_STR = 2,
	D_QUOTED_STR = 3,
	NOT_CLOSED_S_QUOTE_STR = 4,
	NOT_CLOSED_D_QUOTE_STR = 5,
	// FILE_NAME = 2,
	ENV_VAR = 6,
	REDIRECT_OUT_CONCAT = 7,
	HERE_DOC = 8,
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	SPACE_CAHR = ' ',
	TAB_CHAR = '\t',
	NEW_LINE = '\n',
	S_QUOTE = '\'',
	D_QUOTE = '"',
	ESCAPE_CHAR = '\\',
	PIPE = '|',
	DOLLAR_CHAR = '$',
}	t_type;

typedef enum s_quotation
{
	NOT_QUOTED = 1,
	IN_S_QUOTE,
	IN_D_QUOTE,
}	t_quotation;

typedef enum s_quote_status
{
	NO_QUOTE = -1,
	CLOSED_QUOTE = 0,
	OPEN_QUOTE = 1,
	OPEN_AND_CLOSED_PAIRS = 2,
}	t_quote_status;

typedef enum s_white_space
{
	UNKNOWN_WHITE_SPACE = -1,
	NOT_FOLLOWED_BY_WHITE_SPACE = 0,
	FOLLOWED_BY_WHITE_SPACE = 1,

}	t_white_space;

typedef struct s_token_data
{
	int				list_size;
	int				str_len;
	int				type;
	int				quotation;
	char			*str;
	t_quote_status	quote_status;
	t_white_space	white_space;
}	t_token_data;

#endif
