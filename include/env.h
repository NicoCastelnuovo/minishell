/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/06 12:23:59 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/*
	NOTES and STUFF TO DO:
	• EXPORT
		- Why _=[last_cmd] is not shown/exported ???
		- Still need to order as ASCII char
		- multiple args handling
		- Each node maybe need a boolean which signs as exportable or non-exportable (and change init_env)
	• ENV
		- Verify with empty env, or decide what happend in case there is nothing - env_cpy still exist?
		- Pay attention on whatsend to child ps
	• UNSET
		- make VARNAME= not a valid input
		- multiple args handling
	• env -i && when creating env_cpy: set $PWD, update $SHLVL accordingly
*/

typedef struct	s_var
{
	char			*name;
	int				name_len;
	char			*value;
	int				value_len;
	struct s_var	*next;
	struct s_var	*prev;
	int				to_export;
}				t_var;

typedef struct	s_env
{
	struct s_var	*head;
	struct s_var	*tail;
	int				size;
}				t_env;

t_var		*env_dlst_new(char *env_var);
void		env_dlst_append(t_env **env, t_var *new);
void		free_env_node(t_var *node);
void		env_dlst_delnode(t_var *node, t_env **env);
void		env_dlst_clear(t_env **env);
void		env_dlst_update(t_var *new_content, t_env **env);

t_env		*init_env(char **env);
void		print_env(t_env *env);
void		unset_env_var(char *name, t_env **env);

void		export(char *name_value, t_env **env);
void		print_exported_env(t_env *env);

#endif
