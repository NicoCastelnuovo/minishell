/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_syntax_err.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:06:20 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/20 16:09:02 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_tkn_type tkn_type)
{
	if (tkn_type == TKN_REDIR_APPEND ||
		tkn_type == TKN_HERE_DOC ||
		tkn_type == TKN_REDIR_IN ||
		tkn_type == TKN_REDIR_OUT)
		return (tkn_type);
	return (0);
}

static int	is_redir_syntax_err(t_tkn_data *next_tkn)
{
	if (is_redir(next_tkn->type))
		return (1);
	if (next_tkn->type == TKN_NEW_LINE ||
		next_tkn->type == TKN_TAB_CHAR ||
		next_tkn->type == TKN_PIPE) // note sure about this
		return (1);
	return (0);
}

static int	is_pipe_syntax_err(t_tkn_data *next_tkn)
{
	if (!next_tkn)
		return (1);
	if (next_tkn->type == TKN_PIPE)
		return (1);
	return (0);
}

int	check_for_syntax_err(t_list *tkn)
{
	t_tkn_data	*curr_tkn;
	t_tkn_data	*next_tkn;

	curr_tkn = NULL;
	next_tkn = NULL;
	while (tkn)
	{
		curr_tkn = tkn->content;
		if (curr_tkn->quote_status == OPEN_QUOTE)
			return (syntax_error("quotes"), 1);
		if (tkn->next) // check current-next
		{
			next_tkn = tkn->next->content;
			if (is_redir(curr_tkn->type) && is_redir_syntax_err(next_tkn))
				return (syntax_error(next_tkn->str), 1);
			if (curr_tkn->type == TKN_PIPE && is_pipe_syntax_err(next_tkn))
				return (syntax_error(next_tkn->str), 1);
		}
		else
		{
			if (is_redir(curr_tkn->type))
				return (syntax_error("newline"), 1);
			if (curr_tkn->type == TKN_PIPE)
				return (syntax_error(curr_tkn->str), 1);
		}
		tkn = tkn->next;
	}
	return (0);
}
