/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:05:34 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/30 09:52:03 by fahmadia         ###   ########.fr       */
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
