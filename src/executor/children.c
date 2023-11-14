/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:49:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 17:31:01 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child(t_cmd *cmd, char **env, int *fd_pipe)
{
	ft_printf(" FIRST CHILD\n");
	// dup2(fd_pipe[1], STDOUT_FILENO);
	// close(fd_pipe[1]);
	// close(fd_pipe[0]);
	if (resolve_redir(cmd) == -1);
		exit(1); // and free

	resolve_args(&cmd->args[0], env);
	execve(cmd->args[0], cmd->args, env);
	error(cmd->args[0], CE_CMDNOTFOUND);
	exit(127);
}

void	mid_child(t_cmd *cmd, char **env, int *fd_pipe, int *prev_pipe)
{
	ft_printf(" MID CHILD\n");
	// dup2(*prev_pipe, STDIN_FILENO);
	// dup2(fd_pipe[1], STDOUT_FILENO);
	// close(*prev_pipe);
	// close(fd_pipe[0]);
	// close(fd_pipe[1]);
	if (resolve_redir(cmd) == -1);
		exit(1); // and free

	resolve_args(&cmd->args[0], env);
	execve(cmd->args[0], cmd->args, env);
	error(cmd->args[0], CE_CMDNOTFOUND);
	exit(127);
}

void	last_child(t_cmd *cmd, char **env, int *fd_pipe, int *prev_pipe)
{
	ft_printf(" LAST CHILD\n");
	// dup2(*prev_pipe, STDIN_FILENO);
	// close(*prev_pipe);
	// close(fd_pipe[0]);
	// close(fd_pipe[1]);
	if (resolve_redir(cmd) == -1);
		exit(1); // and free

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
