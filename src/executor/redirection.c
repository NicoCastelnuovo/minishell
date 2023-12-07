/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:43:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 14:07:10 by fahmadia         ###   ########.fr       */
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
static int	resolve_redir(t_cmd *cmd)
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

int	redirect_to_explicit(t_node *node)
{
	t_cmd	*cmd;
	int		err;

	cmd = (t_cmd *)node->content;
	err = 0;
	if (cmd->redir)
	{
		if (resolve_redir(cmd) == -1) // error
			return (1);
		else
		{
			if (cmd->fd_in != -2)
			{
				err = dup2(cmd->fd_in, STDIN_FILENO);
				close(cmd->fd_in);
			}
			if (cmd->fd_out != -2)
			{
				err = dup2(cmd->fd_out, STDOUT_FILENO);
				close(cmd->fd_out);
			}
		}
	}
	if (err == -1)
		return (error("dup2", NULL, errno), 1);
	return (0);
}

/*
	if (fd_pipe), means that is a first or a middle child. In case
	fd_pipe == NULL, it means that is the last child.
*/
int	redirect_to_pipes(int *fd_pipe, int *prev_pipe, t_cmd *cmd)
{
	int	fd_ret;

	(void)cmd;
	fd_ret = -1;
	if (fd_pipe)
	{
		// first and mid
		fd_ret = dup2(fd_pipe[1], STDOUT_FILENO);
		// if (fd_ret != -1)
		// 	cmd->fd_out = fd_ret;
		close(fd_pipe[1]);
		fd_ret = dup2(*prev_pipe, STDIN_FILENO); // prev pipe in first child is 0 so already STDIN_FILENO
		// if (fd_ret != -1)
		// 	cmd->fd_in = fd_ret;
		close(fd_pipe[0]);
		close(*prev_pipe);
	}
	else
	{
		// last
		fd_ret = dup2(*prev_pipe, STDIN_FILENO); // protect ?
		// if (fd_ret != -1)
		// 	cmd->fd_in = fd_ret;
		close(*prev_pipe);
	}
	if (fd_ret == -1) // error was here probably !
		return (error("dup2", NULL, errno), 1);
	return (0);
}


// int	redirect_to_pipes(int *fd_pipe, int *prev_pipe, t_cmd *cmd)
// {
// 	int	err;

// 	err = 0;
// 	if (fd_pipe)
// 	{
// 		// first and mid
// 		cmd->fd_in = fd_pipe[1];
// 		cmd->fd_out = *prev_pipe;

// 		err = dup2(cmd->fd_out, STDOUT_FILENO);
// 		close(cmd->fd_out);
// 		err = dup2(*prev_pipe, STDIN_FILENO); // prev pipe in first child is 0 so already STDIN_FILENO
// 		close(cmd->fd_in);
// 		close(*prev_pipe);
// 	}
// 	else
// 	{
// 		// last
// 		err = dup2(*prev_pipe, STDIN_FILENO);
// 		close(*prev_pipe);
// 	}
// 	// if (err == 1) // err -1 or 1
// 	// 	return (error("dup2", NULL, errno), 1);
// 	return (0);
// }
