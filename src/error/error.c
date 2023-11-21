/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:44:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 10:28:40 by ncasteln         ###   ########.fr       */
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
	if (n == CE_SYNTAX_TREE)
		return ("fail building syntax tree");
	if (n == CE_HERE_DOC)
		return ("fail performing here_doc");
	if (n == CE_NUM_REQUIRED)
		return ("numeric argument required");
	if (n == CE_SYNTAX_ERROR)
		return ("syntax error near unexpected token");
	return ("unknow error");
}

static void	basic_err_format(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
}

static void	syntax_err_format(char *s, char *err_message)
{
	ft_putstr_fd(err_message, 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd("'", 2);
	return ;
}

void	error(char *s1, char *s2, int err_id)
{
	char	*err_message;

	err_message = NULL;
	if (err_id < 107)
		err_message = strerror(err_id);
	else
		err_message = custom_strerror(err_id);
	ft_putstr_fd("\e[1;31m* \e[0m", 2);
	ft_putstr_fd("minishell: ", 2);
	if (s1)
	{
		if (err_id == CE_SYNTAX_ERROR)
			return (syntax_err_format(s1, err_message));
		else
			basic_err_format(s1);
	}
	if (s2)
		basic_err_format(s2);
	ft_putendl_fd(err_message, 2);
}
