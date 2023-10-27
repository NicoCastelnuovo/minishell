/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:52:18 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/27 08:21:12 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	pwd command returns the current working path. The function getcwd()
	allocates
*/

char	*get_wd(void)
{
	char	*dir;
	char	*buff;
	size_t	size;

	buff = NULL;
	size = 1;
	// buff = ;
	// while (!buff)
	// {
	// 	size += 1;
	// 	buff = getcwd(buff, size);
	// }
	return (getcwd(NULL, 0));
}

/*
	WWWWWWWWWWWWWWWWWWWW
	TTTTTTTTTTTTTTTTTTTT
	FFFFFFFFFFFFFFFFFFFF
	FFFFFFFFFFFFFFFFFFFF
*/
// char	*get_wd(void)
// {
// 	char	*dir;
// 	char	*buff;
// 	size_t	size;

// 	size = 1;
// 	buff = ft_calloc(size + 1, sizeof(char)); // protect --- create err function!
// 	dir = getcwd(buff, size);
// 	while (!dir)
// 	{
// 		free(buff);
// 		size += 1;
// 		buff = ft_calloc(size + 1, sizeof(char)); // protect --- create err function
// 		dir = getcwd(buff, size);
// 	}
// 	// free (buff);
// 	// buff = NULL;
// 	ft_printf("[%p] and [%p]\n", buff, dir);
// 	return (dir);
// }
