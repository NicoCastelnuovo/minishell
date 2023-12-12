/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pipechain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:49:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/10 17:39:56 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	In order:
		• char **env is prepared to be sent to execve()
		• stdin and stdout are redirected to pipe ends
		• stdin and stdout are redirected to redir (< << >> >)
		• if builtin, it's run separately with proper functions (no execve());
		• if normal cmd, execve() is called
*/
void	child_pipechain(t_data *data, t_node *node, int *pipe, int *prev_pipe)
{
	char	**env;
	t_cmd	*cmd;
	int		ret_value;

	ret_value = 0;
	cmd = (t_cmd *)node->content;
	env = convert_to_dptr(data->env);
	if (!env)
		free_child_and_exit(data, env, 1); // chaged from exit(1);
	if (redirect_to_pipes(pipe, prev_pipe))
		free_child_and_exit(data, env, 1);
	if (redirect_to_explicit(node))
		free_child_and_exit(data, env, 1);
	if (is_builtin(cmd))
		free_child_and_exit(data, env, call_builtin_function(cmd, data));
	if (cmd->args)
	{
		ret_value = resolve_args(&cmd->args[0], env);
		if (ret_value == 126 || ret_value == 127 || ret_value == -1)
			free_child_and_exit(data, env, ret_value);
		if (execve(cmd->args[0], cmd->args, env))
		{
			error(cmd->args[0], NULL, CE_CMDNOTFOUND);
			free_child_and_exit(data, env, 127);
		}
	}
	else
		free_child_and_exit(data, env, 0);
}
