/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:06:20 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/03 12:48:24 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_syntax_err(t_tkn_data *curr, t_tkn_data *next)
{
	ft_printf("   • Check if [%s] & [%s] are valid\n", curr->str, next->str);
	return (0);
}

static int	is_redir(int tkn_type)
{
	if (tkn_type == TKN_REDIRECT_OUT_CONCAT ||
		tkn_type == TKN_HERE_DOC ||
		tkn_type == TKN_REDIRECT_IN ||
		tkn_type == TKN_REDIRECT_OUT )
		return (tkn_type);
	return (0);
}

/*
	Process the tkn and its directly next one, checking for syntax errors.
	If everything is good, the node->content is populated with the t_cmd data.
*/
int	*parse_tkn(t_list *tkn, t_cmd *cmd)
{
	t_tkn_data	*tkn_curr;
	t_tkn_data	*tkn_next;

	tkn_curr = ((t_tkn_data *)tkn->content);
	if (tkn->next)
	{
		tkn_next = ((t_tkn_data *)tkn->next->content);
		ft_printf("PARSE: [%s]\n", tkn_curr->str);
		if (is_redir(tkn_curr->type))
		{
			if (!is_syntax_err(tkn_curr, tkn_next))
			{
				t_redir	*redir_content;

				redir_content = ft_calloc(1, sizeof(t_redir)); // prtct
				redir_content->file_name = tkn_next->str;
				redir_content->type = tkn_curr->type; // correct names
				t_list	*new_redir = ft_lstnew(redir_content);
				ft_lstadd_back(&cmd->redir, new_redir);
				return (0);
			}
			else
				return (1);
		}
	}
	else // final tkn of the input
	{
		ft_printf("PARSE: [%s] (last)\n", tkn_curr->str);
		return (0);
	}
	return (0);
}
