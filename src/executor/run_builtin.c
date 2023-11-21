/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:18:14 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 07:01:20 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd->args)
		return (0);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	return (0);
}

int	run_builtin(t_data *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)data->tree->content;
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		data->e_code = cd(data);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		data->e_code = echo(data);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		data->e_code = exit_custom(data);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		data->e_code = export(data);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		data->e_code = print_env(data->env);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		data->e_code = pwd();
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		data->e_code = unset(data);
	return (data->e_code);
}
