/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:49:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 11:33:25 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child(t_cmd *cmd, char **env, int *fd_pipe)
{
	exit(1);
}

void	mid_child(t_cmd *cmd, char **env, int *fd_pipe)
{
	exit(1);
}

void	last_child(t_cmd *cmd, char **env, int *fd_pipe)
{

	exit(1);
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
