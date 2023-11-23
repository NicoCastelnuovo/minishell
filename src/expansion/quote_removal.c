/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 08:34:59 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/23 09:51:47 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// "ls" | echo $"Hello $USER!" | echo $"USER" | echo "$USER" | echo '$USER' | echo $USER
/*
						---->	ls - executed
	$"Hello ncasteln!"	---->	Hello ncasteln!
	$"USER" 			---->	USER
	-------
	"ncasteln"			---->	ncasteln
	'$USER'				---->	$USER
	ncasteln			---->	ncasteln
*/

// Hello"="world | Hel"lo"=world | He"ll"o=w"or"ld |  He$"ll"o=w$"or"ld
/*
	Hello=world
*/

/*	IDEA
	- cut most external quote always
	(BUT)
	- before need to remove $ if present

	NEW IDEA
	- check after expansion which kind of format it is
		* double or single quotes WITH $
		* double or single quotes WITHOUT $

	CONSEQUENCES
	- echo has to be rebuilt, no need to think now about it
	- "ls" has to be executed for example
	- here_doc doesn't need another trimming
*/

/*
	hell"oworl"d OOOOOOORRRR hello$"$USER$"
*/
/*
	good example
	AAA"'BBB'"CCC'"DDD"'		len = 16		AAA'BBB'CCC"DDD"
	AAA"'BBB'"'"DDD"'CCC		len = 16		AAA'BBB'"DDD"CCC
*/

static char	*copy_without_quotes(char *s, int len)
{
	char	*new_str;
	int		i;
	int		j;
	char	kind_of_quotes;

	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	new_str[len] = '\0';
	i = 0;
	j = 0;
	kind_of_quotes = -1;
	while (s[i])
	{
		if (s[i] == TKN_S_QUOTE || s[i] == TKN_D_QUOTE)
		{
			if (kind_of_quotes == -1)
				kind_of_quotes = s[i];
			else if (kind_of_quotes == s[i])
				kind_of_quotes = -1;
			else
			{
				new_str[j] = s[i];
				j++;
			}
		}
		else
		{
			new_str[j] = s[i];
			j++;
		}
		i++;
	}
	return (new_str);
}

static int	get_len_without_quotes(char *s)
{
	int		i;
	int		len;
	char	kind_of_quotes;

	i = 0;
	len = 0;
	kind_of_quotes = -1;
	while (s[i])
	{
		if (s[i] == TKN_S_QUOTE || s[i] == TKN_D_QUOTE)
		{
			if (kind_of_quotes == -1)
				kind_of_quotes = s[i];
			else if (kind_of_quotes == s[i])
				kind_of_quotes = -1;
			else
				len++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

static char	*remove_quote_pairs(char *s)
{
	int		new_len;
	char	*new_str;

	new_len = get_len_without_quotes(s);
	new_str = copy_without_quotes(s, new_len);
	return (new_str);
}

static int	check_cmd(t_cmd *cmd)
{
	char			*tmp;
	int				i;
	t_list			*redir;
	t_redir_data	*redir_cont;

	tmp = NULL;
	i = 0;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], TKN_D_QUOTE) || ft_strchr(cmd->args[i], TKN_S_QUOTE))
		{
			tmp = cmd->args[i];
			cmd->args[i] = remove_quote_pairs(cmd->args[i]); // check leaks and protect
			ft_printf("FUCKING SHIT RESULT = [%s] !!!\n", cmd->args[i]);
			free(tmp);
			exit (1);
		}
		i++;
	}
	// redir = cmd->redir;
	// while (redir)
	// {
	// 	redir_cont = (t_redir_data * )redir->content;
	// 	// need throw an exception for HERE DOC to understand if it need expansion
	// 	// maybe agood idea to dont do it now but after
	// 	if (ft_strchr(redir_cont->file_name, TKN_D_QUOTE) || ft_strchr(redir_cont->file_name, TKN_S_QUOTE))
	// 	{
	// 		tmp = redir_cont->file_name;
	// 		redir_cont->file_name = remove_quote_pairs(redir_cont->file_name);
	// 		if (redir_cont->file_name)
	// 			return (error("quote removal", NULL, errno), 1);
	// 		// free(tmp);
	// 		// remove outmost
	// 	}
	// 	redir = redir->next;
	// }
}

void	quote_removal(t_data *data)
{
	t_node	*node;
	t_cmd	*cmd;
	t_pipe	*pipe;

	if (!data->tree || data->e_code)
		return ;
	node = data->tree;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		cmd = pipe->left->content;
		if (check_cmd(cmd))
		{
			data->e_code = 1;
			return ;
		}
		node = pipe->right;
	}
	cmd = node->content;
	if (check_cmd(cmd))
		data->e_code = 1;
}





// static char	*remove_quotes(char *s, int first, int second)
// {
// 	int		i;
// 	int		j;
// 	char	*new_str;

// 	new_str = ft_calloc(ft_strlen(s) - 1, sizeof(char)); // protect
// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		if (i == first || i == second)
// 			i++;
// 		new_str[j] = s[i];
// 		j++;
// 		i++;
// 	}
// 	return (new_str);
// }

// /*
// 	The function copy the original string, removing the char at the
// 	specified index (i).
// */
// static char	*remove_char(char *s, int to_remove)
// {
// 	char	*new_str;
// 	int		i;
// 	int		j;

// 	new_str = ft_calloc(ft_strlen(s), sizeof(char)); // no +1 because one is removed
// 	if (!new_str)
// 		return (NULL);
// 	new_str[ft_strlen(s) - 1] = '\0';
// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		if (i == to_remove)
// 			i++;
// 		new_str[j] = s[i];
// 		j++;
// 		i++;
// 	}
// 	return (new_str);
// }

// static int	get_next_quote_index(char *s, char quotes, int skip)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == quotes && skip)
// 		{
// 			skip = 0;
// 			i++;
// 			continue ;
// 		}
// 		if (s[i] == quotes && !skip)
// 		{
// 			return (i);
// 		}
// 		i++;
// 	}
// }

// /*
// 	Returns the first found quotes in the given string.
// */
// static char	get_first_quote_type(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == TKN_D_QUOTE || s[i] == TKN_S_QUOTE)
// 			return (s[i]);
// 		i++;
// 	}
// }

// static char	*remove_quote_pairs(char *s)
// {
// 	char	*new_str;
// 	int		i;
// 	char	*tmp;
// 	char	quotes;
// 	int		next_quote_index;
// 	int		first_quote = -1;
// 	int		second_quote = -1;

// 	tmp = NULL;
// 	new_str = NULL;
// 	i = 0;
// 	while (s[i])					// hello"a"
// 	{
// 		next_quote_index = -1;
// 		if (ft_strchr(s + i, '$') && (s[i + 1] == TKN_S_QUOTE || s[i + 1] == TKN_D_QUOTE))
// 		{
// 			quotes = s[i + 1];
// 			tmp = s;
// 			s = remove_char(s, i);
// 			free(tmp);

// 			next_quote_index = get_next_quote_index(s, quotes, 0);
// 			tmp = s;
// 			s = remove_char(s, next_quote_index);
// 			free(tmp);

// 			next_quote_index = get_next_quote_index(s, quotes, 1);
// 			tmp = s;
// 			s = remove_char(s, next_quote_index);
// 			free(tmp);
// 			// make a jump
// 		}
// 		else
// 		{
// 			if (ft_strchr(s + i, TKN_S_QUOTE) || ft_strchr(s + i, TKN_D_QUOTE))
// 			{
// 				ft_printf("STRING [%s]\n", s + i);
// 				quotes = get_first_quote_type(s + i);
// 				first_quote = get_next_quote_index(s + i, quotes, 0);
// 				ft_printf("Next quotes to rm are [%c] @ original index [%d]...\n", quotes, first_quote);
// 				second_quote = get_next_quote_index(s + i, quotes, 1);
// 				ft_printf("...their pair quotes index [%d]\n", second_quote); // AAAA"'bbbb'"CCCC"'DDDD'"'"eeee"'

// 				s[first_quote] = 127;
// 				s[second_quote] = 127;
// 				// tmp = s;
// 				// s = remove_quotes(s, first_quote, second_quote);
// 				// free(tmp);
// 				ft_printf("Result [%s]\n\n", s);
// 				// jump to ???
// 				i = second_quote;
// 				ft_printf("JUMP TO [%d] at [%c]\n\n", i, s[i]);
// 				exit(1);
// 			}
// 		}
// 		i++;
// 		ft_printf("OFFICIAL JUMP TO [%d] at [%c]\n\n", i, s[i]);
// 	}
// 	return (s);
// }
