/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:44:50 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/26 14:50:46 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# define SPECIAL_CHAR_NUM 10

typedef enum s_type
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
	S_QUOTE = '\'',
	D_QUOTE = '"',
	ESCAPE_CHAR = '\\',
	PIPE = '|',
	DOLLAR_CHAR = '$',
}	t_type;

typedef enum s_position
{
	NOT_QUOTED = 1,
	IN_S_QUOTE,
	IN_D_QUOTE,
}	t_position;

typedef struct s_token_data
{
	int		list_size;
	int		str_len;
	int		type;
	int		position;
	char	*str;
}	t_token_data;

// typedef struct	s_token
// {
// 	t_token_data	*content;
// 	struct s_token	*next;
// }	t_token;

#endif
