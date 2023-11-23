/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:43:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/23 09:12:47 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_with_right_mode(char *file_name, int last_fd, int flags, int mode)
{
	int fd;

	fd = -2;
	if (last_fd >= 0)
		close(last_fd);
	fd = open(file_name, flags, mode);
	if (fd == -1)
		return (error(file_name, NULL, errno), -1);
	return (fd);
}

static int	is_valid_fd(t_cmd *cmd, t_redir_data *redir)
{
	int	fd;
	int	flags;

	flags = -1;
	fd = -2;
	if (redir->type == REDIR_IN || redir->type == REDIR_HERE_DOC)
	{
		flags = O_RDONLY;
		cmd->fd_in = open_with_right_mode(redir->file_name, cmd->fd_in, flags, 0);
		return (cmd->fd_in); // 0 mode is ignored
	}
	else if (redir->type == REDIR_OUT)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		cmd->fd_out = open_with_right_mode(redir->file_name, cmd->fd_out, flags, 0644);
		return (cmd->fd_out);
	}
	else if (redir->type == REDIR_APPEND)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		cmd->fd_out = open_with_right_mode(redir->file_name, cmd->fd_out, flags, 0644);
		return (cmd->fd_out);
	}
	return (fd);
}

/*
	resolve_redir returns (0) in case of open() error and (1) in case of
	success. The function has to stop as soon as an error occurs. The
	last redirection in the list, are the one which are performed, and
	are stored into cmd->fd_in and cmd->fd_out.
*/
int	resolve_redir(t_cmd *cmd)
{
	t_list			*head;
	t_redir_data	*content;
	int				last_fd;

	last_fd = -2;
	head = cmd->redir;
	while (head)
	{
		content = (t_redir_data *)head->content;
		last_fd = is_valid_fd(cmd, content);
		if (last_fd == -1)
			return (-1);
		head = head->next;
	}
	return (0);
}
