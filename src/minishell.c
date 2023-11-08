/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/08 13:46:29 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_empty_line(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (ft_strlen(s) == i)
		return (1);
	return (0);
}

static void	init_data(t_data *data)
{
	data->env = NULL; // need to check in case of empty environment ???
	data->line = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->err = NULL;
	data->e_code = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc > 1 || argv[1])
		return (1); // custom err
	init_data(&data);
	data.env = init_env(env);
	while (1)
	{
		data.line = readline("minishell $ "); // ft_strdup("<in cat -e | wc -l -o  -i >out2 | iuhe"); // readline("minishell $ ");
		if (data.line && !is_empty_line(data.line)) // nest if condition inside
		{
			lexer(data.line, &data.tokens);
			print_tokens(data.tokens);
			if (data.tokens) // can be false ?
			{
				data.err = parse(data.tokens);
				if (data.err)
				{
					data.e_code = 258;
					ft_printf("\033[91msyntax error near unexpected token `%s'\033[0m\n", data.err);
				}
			}
			if (!data.err)
			{
				data.tree = build_syntax_tree(data.tokens, 0);
				print_tokens(data.tokens);
				print_syntax_tree(data.tree);
			}
			free_data(&data);
		}
		// if (data.line) //  && !is_empty_line(line)
		// 	add_history(data.line);
		ft_printf("\033[0;35m===============================================================\033[0m\n");
	}
	return (0);
}





	// line = ft_strdup(" \n\t\t\t\t\tM> \n <<\t\b  | echo$USR ");
	// line = ft_strdup(">\n\n\n\n");
	// line = ft_strdup(">\t    | cat ");
	// line = ft_strdup(" >>\"$USER\" | cat -eb");
	// line = ft_strdup(" \n\t \n <<Hello\t\b  | echo$USR ");
	// line = ft_strdup("$USER <<EOF | cat | abc   $   HOME | \"abc   $ SHLVL   $USER\" >	out2");
	// line = ft_strdup("<<123	<in1<in2  | << EOF<<EOFEFOEF $USER >out3 >>HOME  | cat | cat -e>out2>out1");
	// line = ft_strdup("ls <in -la <in2 cat -e >out1 |  tail -3 | wc | cat b");
	// line = ft_strdup(" >out1 >out2 >out3 >>out4 >ok <in3 |  tail -3 | wc | cat b");
	// line = ft_strdup(" >out1 >out2 >out3 >>out4 >ok <<EOF <in3 <<EOF|  tail -3 | wc | cat b>out9999");
	// line = ft_strdup("<in <<EOF | >out<in");
	// line = ft_strdup("<in>out|>out<in");
