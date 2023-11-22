/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/22 12:12:34 by ncasteln         ###   ########.fr       */
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
	data->prompt = "minishell $ ";
}

static void	shell_loop(t_data *data)
{
	while (1)
	{
		data->input = readline(data->prompt);
		if (!data->input)
			break ;
		if (data->input && !is_empty_input(data->input))
		{
			lexer(data->input, &data->tokens);
			parser(data);
			ft_printf("\033[0;35mBEFORE EXP and QUOTE REMOVAL\033[0;37m\n");
			print_syntax_tree(data->tree);
			expansion(data);
			ft_printf("\033[0;35mAFTER EXP and QUOTE REMOVAL\033[0;37m\n");
			quote_removal(data);
			print_syntax_tree(data->tree);
			// check here_doc after it
			// here_doc(data->tree, data);
			// executor(data);
			// if (is_valid_for_history(data))
			// 	add_history(data->input);
			free_data(data);
			exit(1);
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
	return (0);
}
