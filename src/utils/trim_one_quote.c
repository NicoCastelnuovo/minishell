/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_one_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 07:12:00 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 07:18:20 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Given a strin enclosed by quotes, returns a string with the most outside
	quotes trimmed.
*/
char	*trim_one_quote(char *s)
{
	char	*trimmed;
	size_t	i;
	int		j;

	trimmed = ft_calloc(ft_strlen(s) - 1, sizeof(char)); //protect
	if (!trimmed)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i == 0 || i == ft_strlen(s) - 1)
			i++;
		else
		{
			trimmed[j] = s[i];
			i++;
			j++;
		}
	}
	return (trimmed);
}
