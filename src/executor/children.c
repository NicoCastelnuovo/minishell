/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:49:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/15 14:26:13 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_child(t_node *node, char **env)
{
	// close pipes !!!!!!!!
	free_cmd_node(node);
	free_dptr(env);
	exit(1);
}

void	child(t_node *node, char **env, int *fd_pipe, int *prev_pipe)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)node->content;
	if (fd_pipe)
	{
		// first
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		dup2(*prev_pipe, STDIN_FILENO); // prev pipe in first child is 0 so already STDIN_FILENO
		close(fd_pipe[0]);
		close(*prev_pipe);
	}
	else
	{
		// last
		dup2(*prev_pipe, STDIN_FILENO);
		close(*prev_pipe);
	}
	if (cmd->redir)
	{
		if (resolve_redir(cmd) == -1)
			free_child(node, env);
		else
		{
			if (cmd->fd_in != -2)
			{
				dup2(cmd->fd_in, STDIN_FILENO);
				close(cmd->fd_in);
				// maybe is double close
			}
			if (cmd->fd_out != -2)
			{
				dup2(cmd->fd_out, STDOUT_FILENO);
				close(cmd->fd_out);
				// maybe is double close
			}
		}
	}
	resolve_args(&cmd->args[0], env);
	execve(cmd->args[0], cmd->args, env);
	error(cmd->args[0], NULL, CE_CMDNOTFOUND);
	exit(127);
}

// static void	free_child(t_node *node, char **env)
// {
// 	// close pipes !!!!!!!!
// 	free_cmd_node(node);
// 	free_dptr(env);
// 	exit(1);
// }

// void	first_child(t_node *node, char **env, int *fd_pipe, int *prev_pipe)
// {
// 	t_cmd	*cmd;

// 	cmd = (t_cmd *)node->content;
// 	dup2(fd_pipe[1], STDOUT_FILENO);
// 	close(fd_pipe[1]);
// 	dup2(*prev_pipe, STDOUT_FILENO);
// 	close(fd_pipe[0]);
// 	close(*prev_pipe);
// 	if (cmd->redir)
// 	{
// 		if (resolve_redir(cmd) == -1)
// 			free_child(node, env);
// 		else
// 		{
// 			if (cmd->fd_in != -2)
// 			{
// 				dup2(cmd->fd_in, STDIN_FILENO);
// 				close(cmd->fd_in);
// 				// maybe is double close
// 			}
// 			if (cmd->fd_out != -2)
// 			{
// 				dup2(cmd->fd_out, STDOUT_FILENO);
// 				close(cmd->fd_out);
// 				// maybe is double close
// 			}
// 		}
// 	}
// 	resolve_args(&cmd->args[0], env);
// 	execve(cmd->args[0], cmd->args, env);
// 	error(cmd->args[0], CE_CMDNOTFOUND);
// 	exit(127);
// }

// void	mid_child(t_node *node, char **env, int *fd_pipe, int *prev_pipe)
// {
// 	t_cmd	*cmd;

// 	cmd = (t_cmd *)node->content;
// 	dup2(*prev_pipe, STDIN_FILENO);
// 	dup2(fd_pipe[1], STDOUT_FILENO);
// 	close(*prev_pipe);
// 	close(fd_pipe[0]);
// 	close(fd_pipe[1]);
// 	if (cmd->redir)
// 	{
// 		if (resolve_redir(cmd) == -1)
// 			free_child(node, env);
// 		else
// 		{
// 			if (cmd->fd_in != -2)
// 			{
// 				dup2(cmd->fd_in, STDIN_FILENO);
// 				close(cmd->fd_in);
// 				// maybe is double close
// 			}
// 			if (cmd->fd_out != -2)
// 			{
// 				dup2(cmd->fd_out, STDOUT_FILENO);
// 				close(cmd->fd_out);
// 				// maybe is double close
// 			}
// 		}
// 	}


// 	resolve_args(&cmd->args[0], env);
// 	execve(cmd->args[0], cmd->args, env);
// 	error(cmd->args[0], CE_CMDNOTFOUND);
// 	exit(127);
// }

// void	last_child(t_node *node, char **env, int *fd_pipe, int *prev_pipe)
// {
// 	t_cmd	*cmd;

// 	cmd = (t_cmd *)node->content;
// 	dup2(*prev_pipe, STDIN_FILENO);
// 	close(*prev_pipe);
// 	// close(fd_pipe[0]);
// 	// close(fd_pipe[1]);
// 	if (cmd->redir)
// 	{
// 		if (resolve_redir(cmd) == -1)
// 			free_child(node, env);
// 		else
// 		{
// 			if (cmd->fd_in != -2)
// 			{
// 				dup2(cmd->fd_in, STDIN_FILENO);
// 				close(cmd->fd_in);
// 				// maybe is double close
// 			}
// 			if (cmd->fd_out != -2)
// 			{
// 				dup2(cmd->fd_out, STDOUT_FILENO);
// 				close(cmd->fd_out);
// 				// maybe is double close
// 			}
// 		}
// 	}
// 	resolve_args(&cmd->args[0], env);
// 	execve(cmd->args[0], cmd->args, env);
// 	error(cmd->args[0], CE_CMDNOTFOUND);
// 	exit(127);
// }
