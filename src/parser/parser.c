/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:04:07 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 09:08:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Given the token list, the parser check first for syntax errors. In case of
	syntax error data->e_code is set to 258. The syntax tree is built only if
	there no syntax error.
*/
void	parser(t_data *data)
{
	if (!data->tokens)
		return ;
	if (check_for_syntax_err(data->tokens))
	{
		data->e_code = 2;
		return ;
	}
	data->tree = build_syntax_tree(data->tokens, 0);
	if (!data->tree)
	{
		error(NULL, NULL, CE_SYNTAX_TREE);
		data->e_code = 1;
	}
}
