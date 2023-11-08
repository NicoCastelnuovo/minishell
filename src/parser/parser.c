/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:06:20 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/08 09:54:01 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_tkn_type tkn_type)
{
	if (tkn_type == TKN_REDIR_APPEND ||
		tkn_type == TKN_HERE_DOC ||
		tkn_type == TKN_REDIR_IN || // change !!!
		tkn_type == TKN_REDIR_OUT) // ||
		// tkn_type == REDIR_APPEND ||
		// tkn_type == REDIR_HERE_DOC ||
		// tkn_type == REDIR_IN ||
		// tkn_type == REDIR_OUT )
		return (tkn_type);
	return (0);
}

static int	is_redir_syntax_err(t_tkn_data *curr_tkn, t_tkn_data *next_tkn)
{
	if (next_tkn->type != TKN_WORD)
		return (1);
	return (0);
}

static int	is_pipe_syntax_err(t_tkn_data *curr_tkn, t_tkn_data *next_tkn)
{
	if (!next_tkn)
		return (1);
	if (next_tkn->type == TKN_PIPE)
		return (1);
	return (0);
}

char	*parse(t_list *tkn)
{
	t_tkn_data	*curr_tkn;
	t_tkn_data	*next_tkn;

	while (tkn)
	{
		curr_tkn = NULL;
		next_tkn = NULL;
		curr_tkn = tkn->content;
		if (curr_tkn->quote_status == OPEN_QUOTE)
			return ("quotes");
		if (tkn->next) // check current-next
		{
			next_tkn = tkn->next->content;
			if (is_redir(curr_tkn->type) && is_redir_syntax_err(curr_tkn, next_tkn))
				return (next_tkn->str);
			if (curr_tkn->type == TKN_PIPE && is_pipe_syntax_err(curr_tkn, next_tkn))
				return (next_tkn->str);
		}
		else // check current with end-line
		{
			if (is_redir(curr_tkn->type)) // ------------------ big question: should append a newline during lexing?
				return ("newLine");
			if (curr_tkn->type == TKN_PIPE)
				return (curr_tkn->str);
		}
		tkn = tkn->next;
	}
	return (NULL);
}
