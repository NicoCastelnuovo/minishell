/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dlst_delcontent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:38:23 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/26 11:37:23 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_dlst_delcontent(t_var *var)
{
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	var->name_len = -1;
	var->value_len = -1;
	var->next = NULL;
	var->prev = NULL;
	free(var);
}
