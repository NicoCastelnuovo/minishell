/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:19:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/01 09:46:54 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	perform_here_doc(t_redir_data *redir_cont, t_data *data)
{
	int		fd_tmp;
	char	*tmp_name;
	char	*eof;

	fd_tmp = -1;
	tmp_name = NULL;
	eof = ft_strdup(redir_cont->file_name);
	fd_tmp = get_fd_tmp(redir_cont, fd_tmp, 0);
	if (fd_tmp == -1)
		return (1);
	if (get_interactive_input(fd_tmp, &eof, data))
	{
		free(eof);
		close(fd_tmp);
		return (1);
	}
	free(eof);
	close(fd_tmp);
	return (0);
}

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
