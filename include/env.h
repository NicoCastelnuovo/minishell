/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 14:02:03 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct	s_var
{
	char	*name;
	int		name_len;
	char	*value;
	int		value_len;
}				t_var;

// ------------------------------------------------------------------------ ENV
t_list	*init_env(char **env);
t_var	*create_var_content(char *env_var);
void	del_var_content(void *content);
char	*get_env_custom(char *name, t_list *env);
char	**convert_to_dptr(t_list *env);
int		get_exported_var_n(t_list *env);

#endif
