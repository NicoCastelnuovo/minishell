/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_single_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:25:07 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 10:55:58 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	@line free_child_and_exit(data->tree, env, 0) - this is the case in which
	there is no cmd->args (example when typing line '<<EOF' without anything
	else).
*/
void	child_single_cmd(t_data *data)
{
	char	**env;
	t_cmd	*cmd;

	cmd = (t_cmd *)data->tree->content;
	env = convert_to_dptr(data->env);
	if (!env)
		exit(1);
	if (redirect_to_explicit(data->tree))
		free_child_and_exit(data, env, 1);
	if (cmd->args)
	{
		resolve_args(&cmd->args[0], env);
		if (execve(cmd->args[0], cmd->args, env))
		{
			error(cmd->args[0], NULL, CE_CMDNOTFOUND);
			free_child_and_exit(data, env, 127);
		}
	}
	else
		free_child_and_exit(data, env, 0);
}
