/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:43:44 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 16:51:57 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_pid(int *pid, int n_ps)
{
	int	i;

	i = 0;
	while (i < n_ps)
	{
		free(pid + i);
		i++;
	}
}

/*
	t_data is freed entirely except for the environment, which should survive
	until the program terminates.
*/
void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->pid)
		free_pid(data->pid, data->n_ps);
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tokens)
	{
		ft_lstclear(&data->tokens, del_tokens);
		data->tokens = NULL;
	}
	if (data->tree)
	{
		free_tree(data->tree);
		data->tree = NULL;
	}
	data->n_ps = -1;
}
