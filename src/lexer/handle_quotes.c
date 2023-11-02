/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:09:32 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/02 13:59:06 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_d_quote(t_tkn_data *tkn_data, bool *is_d_q_open, t_quote *quote)
{
	*is_d_q_open = true;
	*quote = IN_D_QUOTE;
	tkn_data->quote_status = OPEN_QUOTE;
}

void	close_d_quote(t_tkn_data *tkn_data, bool *is_d_q_open, t_quote *quote)
{
	*is_d_q_open = false;
	*quote = NOT_QUOTED;
	tkn_data->quote_status = CLOSED_QUOTE;
}

void	open_s_quote(t_tkn_data *tkn_data, bool *is_s_q_open, t_quote *quote)
{
	*is_s_q_open = true;
	*quote = IN_S_QUOTE;
	tkn_data->quote_status = OPEN_QUOTE;
}

void	close_s_quote(t_tkn_data *tkn_data, bool *is_s_q_open, t_quote *quote)
{
	*is_s_q_open = false;
	*quote = NOT_QUOTED;
	tkn_data->quote_status = CLOSED_QUOTE;
}

void	detect_quote(t_tkn_data *tkn_data, char tkn_first_char, t_quote *quote)
{
	static bool	is_s_quote_open = false;
	static bool	is_d_quote_open = false;

	if (tkn_first_char == D_QUOTE && !is_d_quote_open && !is_s_quote_open)
	{
		open_d_quote(tkn_data, &is_d_quote_open, quote);
		printf("double quote is open\n");
	}
	else if (tkn_first_char == D_QUOTE && is_d_quote_open
		&& *quote == IN_D_QUOTE)
	{
		close_d_quote(tkn_data, &is_d_quote_open, quote);
		printf("double quote is closed\n");
	}
	else if (tkn_first_char == S_QUOTE && !is_s_quote_open && !is_d_quote_open)
	{
		open_s_quote(tkn_data, &is_s_quote_open, quote);
		printf("single quote is open\n");
	}
	else if (tkn_first_char == S_QUOTE && is_s_quote_open
		&& *quote == IN_S_QUOTE)
	{
		close_s_quote(tkn_data, &is_s_quote_open, quote);
		printf("single quote is closed\n");
	}
}
