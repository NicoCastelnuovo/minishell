/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/03 15:22:44 by ncasteln         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_env	*env_cpy;
	t_list	*tokens;
	t_node 	*root;

	init_sig_handling();
	env_cpy = init_env(env);


	// PIPECHAIN
	// line = ft_strdup("<in1 cat -e | tail -3 | wc | >out1 cat b");
	line = ft_strdup("<in1 cat -e | tail -3 | << EOF wc | < > | >out1 cat b | echo \"    FckU! \" | head -3 >>out2");
	// line = ft_strdup(" << EOF | < >\">\" >< \"<>>>\" > | echo -n Beautiful -n"); // redirection tries
	// line = ft_strdup("<<      $USER   | cat -e");
	// line = ft_strdup("echo \"   $USER \"     >     out1|   echo      Hello     World");

	// SINGLE CMD
	// line = ft_strdup("echo Hello World, just one command > out1");

	// EMPTY PIPES
	// line = ft_strdup("empty pipes |  |  |  |  | >out1 cat b");
	// line = ft_strdup(" |  |  |  |  |  ");

	// lexer
	tokens = NULL;
	lexer(line, &tokens);
	// print_tokens(tokens);

	// parser
	root = NULL;
	root = build_syntax_tree(tokens, 0);
	if (root)
		print_syntax_tree(root);



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
