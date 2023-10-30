/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:05:34 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/29 19:56:33 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_data(void *content)
{
	t_tkn_data	*token_data;

	token_data = (t_tkn_data *)content;
	if (!token_data)
		return ;
	free(token_data->str);
	free(token_data);
}

void	free_tokens(t_list **token_head)
{
	ft_lstclear(token_head, free_token_data);
}
