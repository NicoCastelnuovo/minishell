/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_for_history.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:38:18 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/13 14:45:02 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_input(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] == ' ') // check also s[i] == '\n' || s[i] == '\t' ???
		i++;
	if (ft_strlen(s) == i)
		return (1);
	return (0);
}

int	is_valid_for_history(t_data *data)
{
	// check empty string ?
	// check ctrl-C ???
	// other ???
	return (1);
}
