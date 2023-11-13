/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:44:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/13 10:27:12 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*custom_strerror(int n)
{
	if (n == CE_INVARG)
		return ("command not found");
	if (n == CE_CMDNOTFOUND)
		return ("command not found");
	return ("unknow error");
}

void	error(char *what_failed, int n)
{
	char	*err_msg;

	err_msg = NULL;
	if (n < 107)
		err_msg = strerror(n);
	else
		err_msg = custom_strerror(n);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(what_failed, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
}
