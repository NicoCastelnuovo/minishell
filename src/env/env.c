/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 08:50:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/11 13:00:24 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Outputs the environment variables which are at least an empty string. The
	uninitalized env var are not output like in the standar env builtin.
*/
void	print_env(t_env *env)
{
	t_var	*head;

	head = env->head;
	ft_printf("\033[0;36m============= ENVIRONMENT =============\033[0;37m\n");
	if (env->size)
	{
		while (head)
		{
			if (head->name && head->value)
			{
				ft_putstr_fd(head->name, 1);
				ft_putchar_fd('=', 1);
				ft_putendl_fd(head->value, 1);
			}
			head = head->next;
		}
	}
	ft_printf("\033[0;36m=======================================\033[0;37m\n");
}

static int need_to_be_copied(char *s)
{
	/// example _=
}

/*
	Copies the environment variable of the parent process into a double
	linked list, to be used in the current shell.
*/
t_env	*init_env(char **env)
{
	t_env	*env_cpy;
	t_var	*new_node;
	int		i;

	env_cpy = ft_calloc(1, sizeof(t_env)); // protect
	env_cpy->head = NULL;
	env_cpy->tail = NULL;
	env_cpy->size = 0;
	new_node = NULL;
	i = 0;
	while (env[i])
	{
		new_node = env_dlst_new(env[i]);
		ft_printf("COPIED --> {%s}\n", new_node->name);
		if (!new_node)
			return (env_dlst_clear(&env_cpy), NULL); // free()
		env_dlst_append(&env_cpy, new_node);
		i++;
	}
	return (env_cpy);
}
