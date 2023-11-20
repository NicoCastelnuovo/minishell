/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/20 09:28:30 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_data *data, char **env)
{
	data->env = init_env(env); // need to check in case of empty environment ???
	data->input = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->e_code = 0;
	data->n_ps = 0;
	data->pid = NULL;
}

static void	shell_loop(t_data *data)
{
	while (1)
	{
		data->input = readline("minishell $ ");
		if (!data->input)
			exit_custom(data);
		if (data->input && !is_empty_input(data->input))
		{
			lexer(data->input, &data->tokens);
			parser(data);
			if (data->tree) //if (!data->e_code)
				expansion(data->tree, data->env, data->e_code);
			//if (!data->e_code)
			here_doc(data->tree, data);
			//if (!data->e_code)
			executor(data);
		}
		// if (is_valid_for_history(data))
		// 	add_history(data->input); // not always to do
		free_data(data);
	}
}

int	main(int argc, char **argv, char **env) // env[0] = NULL
{
	t_data	data;

	if (argc > 1 || argv[1])
		return (error("argc/argv", NULL, CE_INVARG), CE_INVARG);
	init_data(&data, env);
	init_sig_handling();
	shell_loop(&data);
	return (0);
}
