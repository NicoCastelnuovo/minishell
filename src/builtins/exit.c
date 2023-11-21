/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:06:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 09:43:48 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	bye_bye(t_data *data, int last_e_code)
{
	free_data(data);
	ft_lstclear(&data->env, del_var_content);
	exit(last_e_code);
	// print exit in the right way !
}

static int	is_valid_number(char *s)
{
	int		n;
	size_t	i;

	n = ft_atoi(s);
	i = 0;
	if (!n)
	{
		while (s[i] == '0')
			i++;
		if (i != ft_strlen(s))
			return (0);
	}
	return (1);
}

int	exit_custom(t_data *data)
{
	t_cmd	*cmd;
	int		n;

	n = 0;
	cmd = (t_cmd *)data->tree->content;
	while (cmd->args[n])
		n++;
	if (n == 1)
		bye_bye(data, data->e_code);
	else if (n == 2)
	{
		if (is_valid_number(cmd->args[1]))
			bye_bye(data, ft_atoi(cmd->args[1]) % 256);
		else
		{
			error("exit", cmd->args[1], CE_NUM_REQUIRED);
			bye_bye(data, 255);
		}
	}
	else // n > 2
		data->e_code = 1;
	return (error("exit", NULL, CE_TOOMANYARGS), 1);
}
