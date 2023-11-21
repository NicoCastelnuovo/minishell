/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:52:18 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 12:26:02 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	pwd command returns the current working path. The function getcwd()
	allocates memory that should be freed.
*/
int	pwd(void)
{
	char	*buff;
	size_t	size;

	buff = NULL;
	size = 1;
	buff = ft_calloc(size + 1, sizeof(char)); // protect --- create err function!
	buff = getcwd(buff, size);
	while (!buff)
	{
		free(buff);
		size += 1;
		buff = ft_calloc(size + 1, sizeof(char)); // protect --- create err function
		buff = getcwd(buff, size);
	}
	if (!buff)
		return (1);
	ft_putendl_fd(buff, 1);
	free (buff);
	return (0);
}
