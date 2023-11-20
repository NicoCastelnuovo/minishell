/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:06:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/20 09:28:22 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_custom(t_data *data)
{
	t_cmd	*cmd;
	int		last_e_code;
	int		n;

	cmd = (t_cmd *)data->tree->content;
	n = 0;
	while (cmd->args[n])
		n++;
	if (n > 1)
	{
		data->e_code = 1;
		return (error("exit", NULL, CE_TOOMANYARGS), 1);
	}
	if (!data->tree) // come from signal
	{
		ft_putstr_fd("exit", 1);
		free_data(data);
		ft_lstclear(&data->env, del_var_content);
		exit(data->e_code);
	}
	ft_putendl_fd("exit", 1);
	if (!cmd->args[1])
	{
		last_e_code = data->e_code;
		free_data(data);
		ft_lstclear(&data->env, del_var_content);
		exit(last_e_code);
	}
	if (ft_atoi(cmd->args[1]) == 0) // if result of atoi is 0 but the arg is not zero
	{
		if (ft_strcmp(cmd->args[1], "0")) // need to check 0000000000000
		{
			error("exit", NULL, 1); // change err identifier
			free_data(data);
			ft_lstclear(&data->env, del_var_content);
			exit(255);
		}
	}
	else
	{
		free_data(data);
		ft_lstclear(&data->env, del_var_content);
		exit(ft_atoi(cmd->args[1]) % 256);
	}
	return (0);
}
