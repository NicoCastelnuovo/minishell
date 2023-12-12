/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/10 17:51:42 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_data *data, char **env)
{
	data->env = init_env(env);
	if (!data->env)
	{
		error("init_data", NULL, CE_INITENV);
		exit(CE_INITENV);
	}
	data->input = NULL;
	data->tokens = NULL;
	data->tree = NULL;	data->e_code = 0;
	data->n_ps = 0;
	data->pid = NULL;
	data->prompt = "minishell $ ";
}

static void	is_ctrl_c_pressed(t_data *data)
{
	if (g_ctrl_c_pressed)
	{
		data->e_code = 1;
		g_ctrl_c_pressed = 0;
	}
}

static void	shell_loop(t_data *data)
{
	while (1)
	{
		init_sig_handling();
		data->input = readline(data->prompt);
		change_sig_handling();
		is_ctrl_c_pressed(data);
		if (!data->input)
			break ; // ----> print exit && check if call exit_custom()
		if (ft_strlen(data->input) != 0)
		{
			lexer(data->input, &data->tokens);
			parser(data);
			expansion(data);
			quote_removal(data);
			here_doc(data->tree, data);
			executor(data);
			add_history(data->input);
			// printf("g_sig_num = %d\n", g_sig_num);
			free_data(data);
			// exit_custom(NULL, data); // ---> remove!
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc > 1 || argv[1])
		return (error("argc/argv", NULL, CE_INVARG), CE_INVARG);
	init_data(&data, env);
	shell_loop(&data);
	free_data(&data);
	ft_lstclear(&data.env, del_var_content);
	rl_clear_history(); // check if it's correct and put also in: here_doc maybe, exits, children etc
	return (0);
}
