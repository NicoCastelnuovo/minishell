/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:05:34 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/09 11:57:35 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_tokens(void *content)
{
	t_tkn_data	*token_data;

	token_data = (t_tkn_data *)content;
	if (!token_data)
		return ;
	if (token_data->str)
		free(token_data->str);
	// token_data->list_size = -2; // change
	// token_data->type = -2;
	// token_data->quote = -2;
	// token_data->quote_status = -2;
	// token_data->str_len = -2;
	// token_data->white_space = -2;
	free(token_data);
	token_data = NULL;
}
