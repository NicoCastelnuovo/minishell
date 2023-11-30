/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:19:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/30 14:47:21 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_here_doc(t_list *redir, t_data *data)
{
	t_redir_data	*redir_content;

	if (!redir)
		return (0);
	while (redir)
	{
		redir_content = redir->content;
		if (redir_content->type == REDIR_HERE_DOC)
		{
			if (perform_here_doc(redir_content, data))
			{
				data->e_code = 1;
				return (1);
			}
		}
		redir = redir->next;
	}
	return (0);
}

void	here_doc(t_node *tree, t_data *data)
{
	t_pipe	*pipe;
	t_cmd	*cmd;

	if (data->e_code || !data->tree)
		return ;
	while (tree->type == IS_PIPE)
	{
		pipe = tree->content;
		cmd = (t_cmd *)pipe->left->content;
		if (check_here_doc(cmd->redir, data))
			return ;
		tree = pipe->right;
	}
	cmd = (t_cmd *)tree->content;
	check_here_doc(cmd->redir, data);
}
