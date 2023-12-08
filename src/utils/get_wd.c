/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:34:22 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 11:42:03 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_wd(void)
{
	char	*buff;
	size_t	size;

	buff = NULL;
	size = 1;
	buff = ft_calloc(size + 1, sizeof(char));
	if (!buff)
		return (NULL);
	buff = getcwd(buff, size);
	while (!buff)
	{
		free(buff);
		size += 1;
		buff = ft_calloc(size + 1, sizeof(char));
		if (!buff)
			return (NULL);
		buff = getcwd(buff, size);
	}
	return (buff);
}
