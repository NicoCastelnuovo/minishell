/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_content_str_of_two_nodes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:40:11 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/29 12:56:46 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_two_strs(char **cur_str, char *next_str)
{
	char	*temp;

	temp = *cur_str;
	*cur_str = ft_strjoin(*cur_str, next_str); //next_tkn_data->str == NULL?
	free(temp);
	return (*cur_str);
}
