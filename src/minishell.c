/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/02 10:34:39 by ncasteln         ###   ########.fr       */
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

	init_sig_handling();
	env_cpy = init_env(env);
	tokens = NULL;



	line = ft_strdup("<in1 cat -e | tail -3 | wc | >out1 cat b");
	lexer(line, &tokens);
	t_node *root = parse(tokens, 0);
	print_syntax_tree(root);
	// ft_printf("PIPE LEFT ---> [%s]\n", ((t_tkn_data *)root->content->pipe->left->content->cmd->block->content)->str);
	// ft_printf("PIPE LEFT ---> [%s]\n", ((t_tkn_data *)root->content->pipe->left->content->cmd->block->next->content)->str);
	// ft_printf("PIPE LEFT ---> [%s]\n", ((t_tkn_data *)root->content->pipe->left->content->cmd->block->next->next->content)->str);

	// while (1)
	// {
		// line = readline("minishell $ ");
		// if (line && !is_empty_line(line))
		// 	add_history(line);
		// if (line)
		// 	free(line);
	// }
	return (0);
}
