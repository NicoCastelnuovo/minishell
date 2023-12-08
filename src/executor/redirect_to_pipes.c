/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_to_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:44:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/08 13:27:46 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	if (fd_pipe), means that is a first or a middle child. In case
	fd_pipe == NULL, it means that is the last child.
*/
int	redirect_to_pipes(int *fd_pipe, int *prev_pipe)
{
	int	fd_ret;

	fd_ret = -1;
	if (fd_pipe)
	{
		// first and mid
		fd_ret = dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		fd_ret = dup2(*prev_pipe, STDIN_FILENO);
		close(fd_pipe[0]);
		close(*prev_pipe);
	}
	else
	{
		// last
		fd_ret = dup2(*prev_pipe, STDIN_FILENO); // maybe take outside
		close(*prev_pipe);
	}
	if (fd_ret == -1)
		return (error("dup2", NULL, errno), 1);
	return (0);
}
