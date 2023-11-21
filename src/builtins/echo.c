/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 16:56:59 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Iterate through the tkn list, until the argument (i) is reached. Then the
	information hold by t_white_space is read, to understand if the token is
	follwed by white space or not.
*/
static int	needs_whitespace(t_list *tkn, int i)
{
	t_list	*head;
	int		j;

	head = tkn;
	j = 0;
	while (j != i)
	{
		j++;
		head = head->next;
		if (!head)
			return (0);
	}
	if (((t_tkn_data *)head->content)->white_space == FOLLOWED_BY_WHITE_SPACE)
		return (1);
	return (0);
}

/*
	@param i: starting point from which print the argument. In case of option -n
	the first argument to be printed ist the number 2.
*/
static int	echo_args(t_cmd *cmd, t_list *tkn, int i)
{
	char	*tmp;

	tmp = NULL;
	while (cmd->args[i])
	{
		// if (cmd->args[i][0] == TKN_D_QUOTE || cmd->args[i][0] == TKN_S_QUOTE)
		// {
		// 	tmp = trim_one_quote(cmd->args[i]);
		// 	if (!tmp)
		// 		return (error("echo", NULL, errno), 1);
		// 	ft_putstr_fd(tmp, 1);
		// 	free(tmp);
		// }
		// else
			ft_putstr_fd(cmd->args[i], 1);
		if (needs_whitespace(tkn, i))
			ft_putchar_fd(' ', 1);
		i++;
	}
	return (0);
}

/*
	echo writes any oprand to stdout separated by a single blank char, and
	followed by a new line. As the subject states, it has to be implemented
	with the optional -n argument.
*/
int	echo(t_data *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)data->tree->content;
	if (cmd->args[1] && ft_strcmp("-n", cmd->args[1]) == 0)
		return (echo_args(cmd, data->tokens, 2));
	echo_args(cmd, data->tokens, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
