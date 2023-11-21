/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:36:57 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 17:06:07 by ncasteln         ###   ########.fr       */
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

// static int	args_expansion(t_cmd *cmd, t_list *env, int e_code)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	if (cmd->args)
// 	{
// 		while (cmd->args[i])
// 		{
// 			if (ft_strchr(cmd->args[i], '$'))
// 			{
// 				if (cmd->args[i][0] == '$')
// 				{
// 					if (cmd->args[i][1] == TKN_S_QUOTE)
// 					{
// 						// $HELLO -> HELLO
// 						tmp = cmd->args[i];
// 						cmd->args[i] = ft_strdup(cmd->args[i] + 1); // protect
// 						ft_printf("Result (1) -> {%s}\n", cmd->args[i]);
// 						free(tmp);
// 						tmp = cmd->args[i];
// 						cmd->args[i] = trim_one_quote(cmd->args[i]);
// 						free(tmp);
// 						i++;
// 						continue ;
// 					}
// 					else if (cmd->args[i][1] == TKN_D_QUOTE)
// 					{
// 						tmp = cmd->args[i];
// 						cmd->args[i] = ft_strdup(cmd->args[i] + 1); // protect
// 						ft_printf("Result (1) -> {%s}\n", cmd->args[i]);
// 						free(tmp);
// 						tmp = cmd->args[i];
// 						cmd->args[i] = trim_one_quote(cmd->args[i]);
// 						free(tmp);
// 					}
// 				}
// 				if (cmd->args[i][0] != TKN_S_QUOTE)
// 				{
// 					cmd->args[i] = expand(cmd->args[i], env, e_code);
// 					if (cmd->args[i] == NULL)
// 						return (error(cmd->args[i], NULL, CE_EXPANSION), 1);
// 				}
// 			}
// 			i++;
// 		}
// 	}
// 	return (0);
// }

// static int	args_expansion(t_cmd *cmd, t_list *env, int e_code)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	if (cmd->args)
// 	{
// 		while (cmd->args[i])
// 		{
// 			if (ft_strchr(cmd->args[i], '$'))
// 			{
// 				// case of $'(...)' -> rmoves $ and go one step further
// 				if (cmd->args[i][0] == '$' && cmd->args[i][1] == TKN_S_QUOTE)
// 				{
// 					tmp = cmd->args[i];
// 					cmd->args[i] = ft_strdup(cmd->args[i] + 1); // protect
// 					free(tmp);
// 					i++;
// 					// dont continue to expand, restart from while
// 					continue ; // ----> not working anymore
// 				}
// 				// case of $"(...)" -> need to go on and not expand
// 				else if (cmd->args[i][0] == '$' && cmd->args[i][1] == TKN_D_QUOTE)
// 				{
// 					tmp = cmd->args[i];
// 					cmd->args[i] = ft_strdup(cmd->args[i] + 1); // protect
// 					free(tmp);
// 					// dont trim now
// 				}

// 				// expand
// 				cmd->args[i] = expand(cmd->args[i], env, e_code);
// 				ft_printf("BEfore trimming {%s}\n", cmd->args[i]);

// 				// quote removal check !!
// 				if (cmd->args[i][0] == TKN_S_QUOTE || cmd->args[i][0] == TKN_D_QUOTE)
// 				{
// 					tmp = cmd->args[i];
// 					cmd->args[i] = trim_outmost_quotes(cmd->args[i]); // protect
// 					free(tmp);
// 					if (cmd->args[i] == NULL)
// 						return (error(cmd->args[i], NULL, CE_EXPANSION), 1);
// 				}
// 			}
// 			i++;
// 		}
// 	}
// 	return (0);
// }

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
