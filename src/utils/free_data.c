/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:43:44 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/09 12:14:39 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tokens)
	{
		ft_lstclear(&data->tokens, del_tokens);
		// free(data->tokens);
		// data->tokens = NULL;
	}
	if (data->tree)
	{
		free_tree(data->tree);
		data->tree = NULL;
	}
	if (data->err)
	{
		free(data->err);
		data->err = NULL;
	}
	// don't reset e_code !!!!
}
