/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exported_var_n.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:52:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/30 10:39:29 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Counts the number of variables whose value is not NULL.
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
		if (var->value)
			n++;
		env = env->next;
	}
	return (n);
}
