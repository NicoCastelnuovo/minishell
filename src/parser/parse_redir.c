/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:22:05 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/07 10:30:09 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_tkn_type tkn_type)
{
	if (tkn_type == TKN_REDIR_APPEND ||
		tkn_type == TKN_HERE_DOC ||
		tkn_type == TKN_REDIR_IN ||
		tkn_type == TKN_REDIR_OUT )
		return (tkn_type);
	return (0);
}

int	is_redir_syntax_err(t_tkn_data *curr_tkn, t_tkn_data *next_tkn)
{
	if (is_redir(next_tkn->type))
	{
		ft_printf("   ❌ error near unexpected token \'%s\'\n", next_tkn->str);
		return (258);
	}
	return (0);
}

/*
	Add the current redirection token to the list of redirections of the command
	table, and changes the next token type to "TKN_FILE_NAME", so that it can
	be catched in the next iteration.
*/
void	update_cmd_tab_redir_type(t_cmd *cmd, t_tkn_data *tkn_curr, t_tkn_data *tkn_next)
{
	// t_redir	*redir_content;
	// t_list	*new_redir;

	// redir_content = ft_calloc(1, sizeof(t_redir)); // prtct
	// redir_content->file_name = tkn_next->str;
	// redir_content->type = tkn_curr->type; // correct names
	// new_redir = ft_lstnew(redir_content);
	// tkn_next->type = TKN_FILE_NAME;
	// ft_lstadd_back(&cmd->redir, new_redir);
	// if (redir_content->type == TKN_HERE_DOC)
	// 	ft_printf("   • Added type [<<] to redir\n");
	// else if (redir_content->type == TKN_REDIR_APPEND)
	// 	ft_printf("   • Added type [>>] to redir\n");
	// else
	// 	ft_printf("   • Added type [%c] to redir\n", redir_content->type);
}

void	update_cmd_tab_redir_filename(t_cmd *cmd, t_tkn_data *tkn_curr)
{
	t_redir	*last;

	last = ft_lstlast(cmd->redir)->content;
	last->file_name = tkn_curr->str;
	ft_printf("   • Added filename [%s] to redir\n", last->file_name);
}
