/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:44:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/15 14:24:59 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*custom_strerror(int n)
{
	if (n == CE_INVARG)
		return ("invalid arguments");
	if (n == CE_TOOMANYARGS)
		return ("too many arguments");
	if (n == CE_CMDNOTFOUND)
		return ("command not found");
	if (n == CE_INVALIDIDENTIFIER)
		return ("not a valid identifier");
	return ("unknow error");
}

void	error(char *s1, char *s2, int err_id)
{
	char	*err_msg;

	err_msg = NULL;
	if (err_id < 107)
		err_msg = strerror(err_id);
	else
		err_msg = custom_strerror(err_id);
	ft_putstr_fd("\e[1;31m* \e[0m", 2);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	if (s2)
	{
		ft_putstr_fd(s2, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(err_msg, 2);
}
