/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:44:50 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/27 12:31:16 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define SPECIAL_CHAR_NUM 10

typedef enum s_type
{
	WORD = 1,
	// FILE_NAME = 2,
	// ENV_VAR = 3,
	// REDIRECT_OUT_CONCAT = 4,
	// HERE_DOC = 5,
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	WHITESPACE = ' ',
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

typedef struct s_token_data
{
	int		list_size;
	int		str_len;
	int		type;
	int		quotation;
	char	*str;
}	t_token_data;

#endif
