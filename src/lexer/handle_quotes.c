/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:09:32 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/26 15:27:18 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_d_quote(bool *is_d_quote_open, t_position *position)
{
	*is_d_quote_open = true;
	*position = IN_D_QUOTE;
}

static void	close_d_quote(bool *is_d_quote_open, t_position *position)
{
	*is_d_quote_open = false;
	*position = NOT_QUOTED;
}

static void	open_s_quote(bool *is_s_quote_open, t_position *position)
{
	*is_s_quote_open = true;
	*position = IN_S_QUOTE;
}

static void	close_s_quote(bool *is_s_quote_open, t_position *position)
{
	*is_s_quote_open = false;
	*position = NOT_QUOTED;
}

void	detect_quote(char tkn_first_char, t_position *position)
{
	static bool	is_s_quote_open = false;
	static bool	is_d_quote_open = false;

	if (tkn_first_char == D_QUOTE && !is_d_quote_open && !is_s_quote_open)
	{
		open_d_quote(&is_d_quote_open, position);
		printf("double quote is open\n");
	}
	else if (tkn_first_char == D_QUOTE && is_d_quote_open
		&& *position == IN_D_QUOTE)
	{
		close_d_quote(&is_d_quote_open, position);
		printf("double quote is closed\n");
	}
	else if (tkn_first_char == S_QUOTE && !is_s_quote_open && !is_d_quote_open)
	{
		open_s_quote(&is_s_quote_open, position);
		printf("single quote is open\n");
	}
	else if (tkn_first_char == S_QUOTE && is_s_quote_open
		&& *position == IN_S_QUOTE)
	{
		close_s_quote(&is_s_quote_open, position);
		printf("single quote is closed\n");
	}
}
