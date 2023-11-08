/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/08 10:56:38 by ncasteln         ###   ########.fr       */
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
	data->env = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->err = NULL;
	data->e_code = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*line;

	init_data(&data);
	data.env = init_env(env);

	line = ft_strdup(" >>\"$USER\" | cat -eb");
	// line = ft_strdup(" \n\t> \n <<\t\b  | echo$USR ");

	// line = ft_strdup(" \n\t \n <<Hello\t\b  | echo$USR ");
	// line = ft_strdup("$USER <<EOF | cat | abc   $   HOME | \"abc   $ SHLVL   $USER\" >	out2");
	// line = ft_strdup("<<123	<in1<in2  | << EOF<<EOFEFOEF $USER >out3 >>HOME  | cat | cat -e>out2>out1");
	// line = ft_strdup("<in1 cat -e |  tail >out1 <out2 >in3 -3 | <<EOF wc -l | cat b >out2");
	// line = ft_strdup("ls <in -la <in2 cat -e >out1 |  tail -3 | wc | cat b");
	// line = ft_strdup(" >out1 >out2 >out3 >>out4 >ok <in3 |  tail -3 | wc | cat b");
	// line = ft_strdup(" >out1 >out2 >out3 >>out4 >ok <<EOF <in3 <<EOF|  tail -3 | wc | cat b>out9999");
	// line = ft_strdup("<in <<EOF | >out<in");
	// line = ft_strdup("<in>out|>out<in");


	// lexer
	if (line)
		lexer(line, &data.tokens);
	free(line);
	ft_printf("• TOKENS ---> ");
	print_tokens(data.tokens);
	ft_printf("\n");

	// parse
	if (data.tokens)
	{
		data.err = parse(data.tokens);
		if (data.err)
		{
			data.e_code = 258;
			ft_printf(" ❌ syntax error near unexpected token `%s'\n", data.err);
			return (1);
		}
	}



	data.tree = build_syntax_tree(data.tokens, 0);
	print_tokens(data.tokens);
	print_syntax_tree(data.tree);


	// free_data(&data);
	return (0);
}

// while (1)
// {
	// line = readline("minishell $ ");
	// if (line && !is_empty_line(line))
	// 	add_history(line);
	// if (line)
	// 	free(line);
// }
