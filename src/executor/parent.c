/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:49:16 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/20 12:01:59 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_wstatus(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus) + 128);
	return (0);
}

static int	wait_children(pid_t *ps_id, int n_cmd)
{
	int		wstatus;
	int		exit_code;
	pid_t	w_pid;
	int		i;

	exit_code = 0;
	i = 0;
	while (i < n_cmd)
	{
		w_pid = waitpid(ps_id[i], &wstatus, 0);
		// if (w_pid == -1)
		// 	return (error("waitpid", NULL, errno), 1);
		if (w_pid == ps_id[i])
			exit_code = check_wstatus(wstatus);
		i++;
	}
	return (exit_code);
}

int	parent(t_data *data)
{
	data->e_code = wait_children(data->pid, data->n_ps);
	// can return 1 ???
	return (0);
}
