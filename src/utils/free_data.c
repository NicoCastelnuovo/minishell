/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:43:44 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/06 12:49:18 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->tokens)
		ft_lstclear(&data->tokens, del_tokens);
	if (data->env)
		env_dlst_clear(&data->env);
	if (data->tree)
		free_tree(data->tree);
}
