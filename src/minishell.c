/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/06 11:13:58 by ncasteln         ###   ########.fr       */
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
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*line;

	init_data(&data);
	// init_sig_handling();
	data.env = init_env(env);


	// lexer
	// add a pre-check for line
	if (line)
		lexer(line, &data.tokens);

	// tree
	// data.tree = ftcalloc (...)
	data.tree = build_syntax_tree(data.tokens, 0);
	// check if data.tree
	print_syntax_tree(data.tree);

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






	// line = ft_strdup(">");
	// line = ft_strdup("<");
	// line = ft_strdup("<<");
	// line = ft_strdup("> > > > >");
	// line = ft_strdup(">> >> >> >>");
	// line = ft_strdup(">>>>>>>>>");
	// line = ft_strdup("<<<<<<<<<");
	// line = ft_strdup("~");
	// line = ft_strdup("< < < < < <");
	// line = ft_strdup("/bin/cat ><");
	// line = ft_strdup("/bin/cat <Makefile >");
	// line = ft_strdup("cat 42 42");
	// line = ft_strdup("echo >");
	// line = ft_strdup("echo > <");
	// line = ft_strdup(".");
	// line = ft_strdup("..");
	// line = ft_strdup("echo | |");
	// line = ft_strdup("EechoE");
	// line = ft_strdup(".echo.");


	// PIPECHAIN
	line = ft_strdup("<in1 cat -e |  tail -3 | wc | cat b");
	// line = ft_strdup("<in1 cat -e | tail -3 | << EOF wc | >out1 cat b | echo \"    FckU! \" | head -3 >>out2");
	// line = ft_strdup("<<      $USER   | cat -e");
	// line = ft_strdup("echo \"   $USER \"     >     out1|   echo      Hello     World");

	// REDIRECTION/PIPE ERRORS
	// line = ft_strdup("<in1 cat -e | > | tail -3 | wc | >out1 cat b");
	// line = ft_strdup(" << EOF | < >\">\" >< \"<>>>\" > | echo -n Beautiful -n");

	// SINGLE CMD
	// line = ft_strdup("echo Hello World, just one command > out1");

	// EMPTY PIPES
	// line = ft_strdup("empty pipes |  |  |  |  | >out1 cat b");
	// line = ft_strdup(" |  |  |  |  |  ");

	// ERRORS
	/*
		Understand when the error is found, how return it and store in the big data
		so that it can be printed in case of $?
	*/
