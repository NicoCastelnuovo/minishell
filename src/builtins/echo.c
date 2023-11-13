/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/13 15:56:49 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	echo writes any oprand to stdout separated by a single blank char, and
	followed by a new line. As the subject states, it has to be implemented
	with the optional -n argument.
*/
void	echo(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)data->tree->content;
	i = 1;
	if (ft_strcmp("-n", cmd->args[1]) == 0)
	{
		i++;
		while (cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], 1);
			i++;
		}
		return ;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}
