/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 08:34:59 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/23 11:28:13 by ncasteln         ###   ########.fr       */
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

/*
	IDEA_2 ???
	* resolve the $"here strings 'need' to 'be 'expanded" in expansion
	* resolve the "no dollar sign before" in quote removal
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
