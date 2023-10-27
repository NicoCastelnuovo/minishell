/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_each_token_string.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:07:54 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/26 15:08:37 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_each_tkn_str(t_token_data *tkn_data)
{
	char	tkn_first_char;

	tkn_first_char = *(tkn_data->str);
	if (tkn_first_char == REDIRECT_IN)
		tkn_data->type = REDIRECT_IN;
	else if (tkn_first_char == REDIRECT_OUT)
		tkn_data->type = REDIRECT_OUT;
	else if (tkn_first_char == WHITESPACE)
		tkn_data->type = WHITESPACE;
	else if (tkn_first_char == NEW_LINE)
		tkn_data->type = NEW_LINE;
	else if (tkn_first_char == S_QUOTE)
		tkn_data->type = S_QUOTE;
	else if (tkn_first_char == D_QUOTE)
		tkn_data->type = D_QUOTE;
	else if (tkn_first_char == ESCAPE_CHAR)
		tkn_data->type = ESCAPE_CHAR;
	else if (tkn_first_char == PIPE)
		tkn_data->type = PIPE;
	else if (tkn_first_char == DOLLAR_CHAR)
		tkn_data->type = DOLLAR_CHAR;
	else
		tkn_data->type = WORD;
}
