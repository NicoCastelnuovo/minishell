/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exported_var_n.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:52:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 11:14:43 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Counts the number of variables with the flag to_export set on true(1).
	Needed before forking, to pass the exported env to the children.
*/
int	get_exported_var_n(t_list *env)
{
	t_var	*var;
	int		n;

	n = 0;
	while (env)
	{
		var = (t_var *)env->content;
		if (var->to_export)
			n++;
		env = env->next;
	}
	return (n);
}
