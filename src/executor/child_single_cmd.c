/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_single_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:25:07 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/08 13:20:16 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_child_and_exit(t_data *data, char **env, int e_code)
{
	// close pipes in case of pipechain !!!!!!!!????
	if (data)
		free_data(data);
	if (env)
		free_dptr(env);
	ft_lstclear(&data->env, del_var_content);
	exit(e_code);
}

/*
	@line free_child_and_exit(data->tree, env, 0) - this is the case in which
	there is no cmd->args (example when typing line '<<EOF' without anything
	else).
*/
void	child_single_cmd(t_data *data)
{
	char	**env;
	t_cmd	*cmd;

	env = convert_to_dptr(data->env);
	if (!env)
		free_child_and_exit(data, env, 1);
	if (redirect_to_explicit(data->tree))
		free_child_and_exit(data, env, 1);
	cmd = (t_cmd *)data->tree->content;
	if (cmd->args)
	{
		if (resolve_args(&cmd->args[0], env) == -1)
			free_child_and_exit(data, env, 1);
		if (execve(cmd->args[0], cmd->args, env))
		{
			error(cmd->args[0], NULL, CE_CMDNOTFOUND);
			free_child_and_exit(data, env, 127);
		}
	}
	else
		free_child_and_exit(data, env, 0);
}
