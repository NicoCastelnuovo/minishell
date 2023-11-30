/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:49:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/30 13:04:38 by ncasteln         ###   ########.fr       */
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
	In order:
		• char **env is prepared to be sent to execve()
		• stdin and stdout are redirected to pipe ends
		• stdin and stdout are redirected to redir (< << >> >)
		• if builtin, it's run separately with proper functions
		• if normal cmd, execve() is called
*/
void	child(t_data *data, t_node *node, int *fd_pipe, int *prev_pipe)
{
	char	**env;
	t_cmd	*cmd;

	cmd = (t_cmd *)node->content;

	env = convert_to_dptr(data->env);
	if (!env)
	{
		error("convert env to dptr", NULL, errno);
		exit(1);
	}

	// redirect to pipes && explicit
	if (redirect_to_pipes(fd_pipe, prev_pipe))
		free_child_and_exit(node, env);


	// arrives here only if not a builtin
	if (redirect_to_explicit(node))
		free_child_and_exit(node, env);


	// if its builtin special thing
	if (is_builtin(cmd))
	{
		exit(call_builtin_function(cmd, data));
	}


	// if normal cmd
	if (cmd->args)
	{
		resolve_args(&cmd->args[0], env);
		if (execve(cmd->args[0], cmd->args, env))
		{
			error(cmd->args[0], NULL, CE_CMDNOTFOUND);
			exit(CE_CMDNOTFOUND);
		}
	}
}
