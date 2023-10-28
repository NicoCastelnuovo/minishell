/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:44:50 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/28 18:47:11 by fahmadia         ###   ########.fr       */
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
	// FILE_NAME = 2,
	ENV_VAR = 4,
	REDIRECT_OUT_CONCAT = 5,
	HERE_DOC = 6,
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
	OPEN_AND_CLOSE_PAIRS = 2,
}	t_quote_status;

typedef struct s_token_data
{
	int				list_size;
	int				str_len;
	int				type;
	int				quotation;
	char			*str;
	t_quote_status	quote_status;
}	t_token_data;

#endif