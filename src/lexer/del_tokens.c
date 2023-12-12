/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:05:34 by fahmadia          #+#    #+#             */
/*   Updated: 2023/12/12 09:03:03 by fahmadia         ###   ########.fr       */
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
	free(token_data);
	token_data = NULL;
}
