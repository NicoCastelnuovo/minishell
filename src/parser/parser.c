/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:06:20 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/03 14:08:37 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Process the tkn and its directly next one, checking for syntax errors.
	If everything is good, the node->content is populated with the t_cmd data.
*/
int	*parse_tkn(t_list **tkn, t_cmd *cmd)
{
	t_tkn_data	*tkn_curr;
	t_tkn_data	*tkn_next;

	tkn_curr = ((t_tkn_data *)(*tkn)->content);
	if ((*tkn)->next)
	{
		tkn_next = ((t_tkn_data *)(*tkn)->next->content);
		ft_printf("PARSE: [%s]\n", tkn_curr->str);
		if (is_redir(tkn_curr->type))
		{
			if (!is_redir_syntax_err(tkn_curr, tkn_next))
			{
				update_cmd_tab_redir_type(cmd, tkn_curr, tkn_next); // prtct
				return (0);
			}
			else
				return (1);
		}
		if (tkn_curr->type == TKN_FILE_NAME)
		{
			update_cmd_tab_redir_filename(cmd, tkn_curr);
			return (0);
		}
	}
	else // final tkn of the input
	{
		ft_printf("PARSE: [%s] (last)\n", tkn_curr->str);
		return (0);
	}
	return (0);
}






// int	*parse_tkn(t_list **tkn, t_cmd *cmd)
// {
// 	t_tkn_data	*tkn_curr;
// 	t_tkn_data	*tkn_next;

// 	tkn_curr = ((t_tkn_data *)(*tkn)->content);
// 	if ((*tkn)->next)
// 	{
// 		tkn_next = ((t_tkn_data *)(*tkn)->next->content);
// 		ft_printf("PARSE: [%s]\n", tkn_curr->str);
// 		if (is_redir(tkn_curr->type))
// 		{
// 			if (!is_syntax_err(tkn_curr, tkn_next))
// 			{
// 				update_cmd_tab_redir(cmd, tkn_curr, tkn_next); // prtct
// 				// t_redir	*redir_content;

// 				// redir_content = ft_calloc(1, sizeof(t_redir)); // prtct
// 				// redir_content->file_name = tkn_next->str;
// 				// redir_content->type = tkn_curr->type; // correct names
// 				// t_list	*new_redir = ft_lstnew(redir_content);
// 				// ft_lstadd_back(&cmd->redir, new_redir);
// 				(*tkn) = (*tkn)->next;
// 				if ((*tkn)->next)
// 				{
// 					ft_printf("   • I jump from [%s]", tkn_curr->str);
// 					ft_printf(" to [%s]\n", ((t_tkn_data *)(*tkn)->next->content)->str);
// 				}
// 				else
// 				{
// 					ft_printf("   • (end-of-input)\n");
// 				}
// 				return (0);
// 			}
// 			else
// 				return (1);
// 		}
// 	}
// 	else // final tkn of the input
// 	{
// 		ft_printf("PARSE: [%s] (last)\n", tkn_curr->str);
// 		return (0);
// 	}
// 	return (0);
// }
