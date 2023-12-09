/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:18:14 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 09:24:16 by ncasteln         ###   ########.fr       */
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

/*
	This function is called for the builtins which are part of a pipeline. They
	have a different function which call the custom functions. Pipes and
	redir are performed before (child() function).
*/
int	call_builtin_function(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		data->e_code = cd(cmd, data);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		data->e_code = echo(data, cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		data->e_code = exit_custom(cmd, data);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		data->e_code = export(cmd, data);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		data->e_code = print_env(data->env);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		data->e_code = pwd();
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		data->e_code = unset(cmd, data);
	return (data->e_code);
}

/*
	This function is called for the builtins which are NOT part of a pipeline.
	They are not part of a pipeline because of some particular features
	(basic example cd). Since there could be a possible redirection, the
	default stdin and stdout need to be dup() to be restored.
*/
int	run_builtin_same_ps(t_data *data)
{
	t_cmd	*cmd;
	int		def_stdin;
	int		def_stdout;

	// some files are not closed ???????
	def_stdin = dup(STDIN_FILENO); // protect
	def_stdout = dup(STDOUT_FILENO); // protect
	if (def_stdin == -1 || def_stdout == -1)
	{
		data->e_code = 1;
		return (error("builtin", NULL, errno), 1);
	}
	if (redirect_to_explicit(data->tree))
	{
		data->e_code = 1;
		return (data->e_code);
	}
	cmd = (t_cmd *)data->tree->content;
	data->e_code = call_builtin_function(cmd, data);
	if (dup2(def_stdin, STDIN_FILENO) == -1 || dup2(def_stdout, STDOUT_FILENO) == -1)
	{
		data->e_code = 1;
		return (error("builtin", NULL, errno), 1);
	}
	return (data->e_code);
}
