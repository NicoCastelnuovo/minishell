/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 12:45:36 by fahmadia         ###   ########.fr       */
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
	data->tree = NULL;
	data->e_code = 0;
	data->n_ps = 0;
	data->pid = NULL;
	data->prompt = "minishell $ ";
}

static void	shell_loop(t_data *data)
{
	while (1)
	{
		// data->input = readline(data->prompt);
		data->input = ft_strdup("$USER$HOME$$$$$?$?$?$$$$"); // -----> valgrind problems
		if (!data->input)
			break ; // ----> print exit && check if call exit_custom()
		if (ft_strlen(data->input) != 0)
		{
			lexer(data->input, &data->tokens);
			parser(data);
			print_syntax_tree(data->tree);
			expansion(data);
			quote_removal(data);
			here_doc(data->tree, data);
			executor(data);
			add_history(data->input);
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
	init_sig_handling();
	shell_loop(&data);
	free_data(&data);
	ft_lstclear(&data.env, del_var_content);
	return (0);
}
