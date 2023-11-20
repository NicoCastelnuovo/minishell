/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:49:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/20 13:57:52 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_child_and_exit(t_node *node, char **env)
{
	// close pipes !!!!!!!!
	free_cmd_node(node);
	free_dptr(env);
	exit(1);
}

/*
	if (fd_pipe), means that is a first or a middle child. In case
	fd_pipe == NULL, it means that is the last child.
*/
static int	redirect_to_pipes(int *fd_pipe, int *prev_pipe)
{
	int	err;

	err = 0;
	if (fd_pipe)
	{
		// first
		err = dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		err = dup2(*prev_pipe, STDIN_FILENO); // prev pipe in first child is 0 so already STDIN_FILENO
		close(fd_pipe[0]);
		close(*prev_pipe);
	}
	else
	{
		// last
		err = dup2(*prev_pipe, STDIN_FILENO);
		close(*prev_pipe);
	}
	if (err == 1)
		return (error("dup2", NULL, errno), 1);
	return (0);
}

static int	redirect_to_explicit(t_node *node, char **env)
{
	t_cmd	*cmd;
	int		err;

	cmd = (t_cmd *)node->content;
	err = 0;
	if (cmd->redir)
	{
		if (resolve_redir(cmd) == -1)
		{
			return (1);
		}
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

static int	redirect_in_out(t_node *node, char **env, int *fd_pipe, int *prev_pipe)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)node->content;
	if (redirect_to_pipes(fd_pipe, prev_pipe))
		free_child_and_exit(node, env);
	if (redirect_to_explicit(node, env))
		free_child_and_exit(node, env);
}

void	child(t_node *node, char **env, int *fd_pipe, int *prev_pipe)
{
	t_cmd	*cmd;

	redirect_in_out(node, env, fd_pipe, prev_pipe);
	cmd = (t_cmd *)node->content;
	if (cmd->args)
	{
		resolve_args(&cmd->args[0], env);
		execve(cmd->args[0], cmd->args, env);
		error(cmd->args[0], NULL, CE_CMDNOTFOUND);
		exit(127);
	}
	// ---- form here
	// ---- unlink() / close()
	exit (0);
}
