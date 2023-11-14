/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:49:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 15:39:01 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child(t_cmd *cmd, char **env, int *fd_pipe, int *prev_pipe)
{
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	close(fd_pipe[0]);

	resolve_redir(cmd);
	ft_printf("CMD->fd in [%d]\n", cmd->fd_in);
	ft_printf("CMD->fd out [%d]\n", cmd->fd_out);
	resolve_args(&cmd->args[0], env);
	execve(cmd->args[0], cmd->args, env);
	error(cmd->args[0], CE_CMDNOTFOUND);
	exit(127);
}

void	mid_child(t_cmd *cmd, char **env, int *fd_pipe, int *prev_pipe)
{
	dup2(*prev_pipe, STDIN_FILENO);
	close(*prev_pipe);
	close(fd_pipe[0]);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);

	resolve_redir(cmd);
	ft_printf("CMD->fd in [%d]\n", cmd->fd_in);
	ft_printf("CMD->fd out [%d]\n", cmd->fd_out);
	resolve_args(&cmd->args[0], env);
	execve(cmd->args[0], cmd->args, env);
	error(cmd->args[0], CE_CMDNOTFOUND);
	exit(127);
}

void	last_child(t_cmd *cmd, char **env, int *fd_pipe, int *prev_pipe)
{
	dup2(*prev_pipe, STDIN_FILENO);
	close(*prev_pipe);
	close(fd_pipe[0]);
	close(fd_pipe[1]);

	resolve_redir(cmd);
	ft_printf("CMD->fd in [%d]\n", cmd->fd_in);
	ft_printf("CMD->fd out [%d]\n", cmd->fd_out);
	resolve_args(&cmd->args[0], env);
	execve(cmd->args[0], cmd->args, env);
	error(cmd->args[0], CE_CMDNOTFOUND);
	exit(127);
}


	// pipe_fd[0]
	// pipe_fd[1]
	// prev_pipe

	// close(fd_pipe[0]);
	// dup2(*prev_pipe, STDIN_FILENO);

	// close(*prev_pipe);

	// dup2(fd_pipe[1], STDOUT_FILENO);
	// close(fd_pipe[1]);

	// child() // (t_cmd *cmd, char **env, int i)
