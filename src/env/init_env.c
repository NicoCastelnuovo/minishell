/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 08:50:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/13 10:48:33 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Copies the environment variable of the parent process into a double
	linked list, to be used in the current shell.
*/
t_list	*init_env(char **env)
{
	t_list	*env_cpy;
	t_list	*new_node;
	t_var	*new_content;
	int		i;

	env_cpy = NULL;
	new_node = NULL;
	i = 0;
	while (env[i])
	{
		new_content = create_var_content(env[i]);
		new_node = ft_lstnew(new_content);
		if (!new_node)
			return (ft_lstclear(&env_cpy, del_var_content), NULL); // free()
		ft_lstadd_back(&env_cpy, new_node);
		i++;
	}
	return (env_cpy);
}
