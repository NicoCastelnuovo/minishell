/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 07:11:46 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_args(char **args)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 2;
	while (args[i])
	{
		if (args[i][0] == TKN_D_QUOTE || args[i][0] == TKN_S_QUOTE)
			tmp = trim_one_quote(args[i]);
		//
		ft_putstr_fd(args[i], 1);
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
	if (ft_strcmp("-n", cmd->args[1]) == 0)
		return (echo_args(cmd->args));
	echo_args(cmd->args);
	ft_putchar_fd('\n', 1);
	return (0);
}
