/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:43:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 15:09:38 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_last_outfile(t_list *redir)
{
	t_redir_data	*content;
	t_redir_data	*last_redir_out;

	while (redir)
	{
		content = (t_redir_data *)redir->content;
		if (content->type == REDIR_OUT || content->type == REDIR_APPEND)
			last_redir_out = content;
		redir = redir->next;
	}
	ft_printf("LAST OUT IS %s\n", last_redir_out->file_name);
	if (last_redir_out->type == REDIR_OUT)
		return (open(last_redir_out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	return (open(last_redir_out->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644));
}

int	get_last_infile(t_list *redir)
{
	t_redir_data	*content;
	t_redir_data	*last_redir_in;

	while (redir)
	{
		content = (t_redir_data *)redir->content;
		if (content->type == REDIR_IN || content->type == REDIR_HERE_DOC)
			last_redir_in = content;
		redir = redir->next;
	}
	ft_printf("LAST IN IS %s\n", last_redir_in->file_name);
	return (open(last_redir_in->file_name, O_RDONLY));
}

void	resolve_redir(t_cmd *cmd)
{
	if (cmd->redir)
	{
		cmd->fd_in = get_last_infile(cmd->redir);
		cmd->fd_out = get_last_outfile(cmd->redir);
	}
}
