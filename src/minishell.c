/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/30 15:29:44 by ncasteln         ###   ########.fr       */
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
	// ft_printf("minishell pid = [%d]\n",getpid());
	while (1)
	{
		data->input = readline(data->prompt);
		if (!data->input)
			break ;
		if (data->input && !is_empty_input(data->input))
		{
			lexer(data->input, &data->tokens);
			parser(data);
			//****************************************************************
			// ft_printf("\033[0;35mBEFORE\033[0;37m\n");
			// print_syntax_tree(data->tree);
			//****************************************************************
			expansion(data);
			quote_removal(data);
			here_doc(data->tree, data);
			//****************************************************************
			// ft_printf("\033[0;35mAFTER\033[0;37m\n"); // hello'"$no expand"'
			// print_syntax_tree(data->tree);
			//****************************************************************
			executor(data);
			if (is_valid_for_history(data))
				add_history(data->input);
			free_data(data);
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
