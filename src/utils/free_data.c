/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:43:44 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/08 13:46:31 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->tokens)
	{
		ft_lstclear(&data->tokens, del_tokens);
		data->tokens = NULL;
	}
	if (data->env)
	{
		env_dlst_clear(&data->env);
		data->env = NULL;
	}
	if (data->tree)
	{
		free_tree(data->tree);
		data->tree = NULL;
	}
	data->err = NULL;
	data->e_code = 0;
}
