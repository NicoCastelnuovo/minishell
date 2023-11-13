/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/13 16:52:03 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_data *data, char **env)
{
	data->env = init_env(env); // need to check in case of empty environment ???
	data->input = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->err = NULL;
	data->e_code = 0;
}

static void	process_input(t_data *data)
{
	lexer(data->input, &data->tokens);
	if (data->tokens) // can be false ?
	{
		data->err = parse(data->tokens);
		if (data->err)
		{
			data->e_code = 258;
			ft_printf("\033[91mminishell: syntax error near unexpected token `%s'\033[0m\n", data->err);
		}
	}
	if (!data->err)
		data->tree = build_syntax_tree(data->tokens, 0);
	if (data->tree)
		expansion(data->tree, data->env, data->e_code);
	here_doc(data->tree, data);
	// if (ft_strcmp(((t_cmd *)data->tree->content)->args[0], "cd") == 0)
	// 	cd(data);
	// if (ft_strcmp(((t_cmd *)data->tree->content)->args[0], "pwd") == 0)
	// 	pwd();
	// if (ft_strcmp(((t_cmd *)data->tree->content)->args[0], "env") == 0)
	// 	get_env(data->env);
	// if (ft_strcmp(((t_cmd *)data->tree->content)->args[0], "export") == 0)
	// 	export(data);
	// if (ft_strcmp(((t_cmd *)data->tree->content)->args[0], "unset") == 0)
	// 	unset(data);
	// if (ft_strcmp(((t_cmd *)data->tree->content)->args[0], "exit") == 0)
	// 	exit_custom(data);
	// if (ft_strcmp(((t_cmd *)data->tree->content)->args[0], "echo") == 0)
	// 	echo(data);
	// execute
}

static void	shell_loop(t_data *data)
{
	while (1)
	{
		data->input = readline("minishell $ ");
		if (!data->input)
		{
			struct termios t;
			tcgetattr(STDIN_FILENO, &t);
			t.c_lflag &= ~ICANON;  // Turn off canonical mode (line-buffered input)
			t.c_cc[VMIN] = 0;      // Set VMIN to 0 for non-blocking read
			tcsetattr(STDIN_FILENO, TCSANOW, &t);
			ft_putendl_fd("FUCK YOU MINISHELL!", 1);
			exit(1);
		}
		if (data->input && !is_empty_input(data->input)) //  && !is_empty_input(data->input)
			process_input(data);
		// if (is_valid_for_history(data))
		// 	add_history(data->input); // not always to do
		free_data(data);
		ft_printf("\033[0;35m=========================================================================\033[0m\n");
	}
}

int	main(int argc, char **argv, char **env) // env[0] = NULL
{
	t_data	data;

	if (argc > 1 || argv[1])
		return (error("argc/argv", CE_INVARG), CE_INVARG);
	init_data(&data, env);
	init_sig_handling();
	shell_loop(&data);
	// if (data.env)
	// 	ft_lstclear(&data.env, del_var_content);
	return (0);
}
