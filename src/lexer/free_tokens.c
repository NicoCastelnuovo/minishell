/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:05:34 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/26 14:48:14 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_data(void *content)
{
	t_token_data	*token_data;

	token_data = (t_token_data *)content;
	if (!token_data)
		return ;
	free(token_data->str);
	free(token_data);
}

void	free_tokens(t_list **token_head)
{
	ft_lstclear(token_head, free_token_data);
}
