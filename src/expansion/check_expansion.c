/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:36:57 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/23 11:35:01 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_expansion(t_cmd *cmd, t_list *env, int e_code)
{
	t_list			*redir;
	t_redir_data	*redir_content;

	redir = (t_list *)cmd->redir;
	redir_content = NULL;
	while (redir)
	{
		redir_content = (t_redir_data *)redir->content;
		if (redir && redir_content->type != REDIR_HERE_DOC)
		{
			if (ft_strchr(redir_content->file_name, '$') && redir_content->file_name[0] != TKN_S_QUOTE)
			{
				redir_content->file_name = expand(redir_content->file_name, env, e_code);
				if (!redir_content->file_name)
					return (error(redir_content->file_name, NULL, CE_EXPANSION), 1);
			}
		}
		redir = redir->next;
	}
	return (0);
}

static int	args_expansion(t_cmd *cmd, t_list *env, int e_code)
{
	int		i;

	i = 0;
	if (cmd->args)
	{
		// example
			// $"hello $USER this is a long string"
			// $"'hello $USER this is a long string'"
			// $'hello $USER this is a long string' --- NOT to be EXPANDED
			// $'"hello $USER this is a long string"' --- NOT to be EXPANDED
			// "world" --- NOTHING to EXPAND
			// "'$USER'"
			// '"$USER"' --- NOT to be EXPANDED
		while (cmd->args[i])
		{
			if (ft_strchr(cmd->args[i], '$'))
			{
				if (cmd->args[i][0] == '$') // $$$$"" && $"" && $''
				{

				}
				if (cmd->args[i][0] != TKN_S_QUOTE)
				{
					cmd->args[i] = expand(cmd->args[i], env, e_code);
					if (cmd->args[i] == NULL)
						return (error(cmd->args[i], NULL, CE_EXPANSION), 1);
				}
			}
			i++;
		}
	}
	return (0);
}

/*
	Iterate through the args and redirections od t_cmd structure, checking
	if there issomething to expand. In case of here_doc, the variable is not
	expanded!
*/
int	check_expansion(t_cmd *cmd, t_list *env, int e_code)
{
	if (args_expansion(cmd, env, e_code))
		return (1);
	if (redir_expansion(cmd, env, e_code))
		return (1);
	return (0);
}
