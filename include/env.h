/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/25 17:00:23 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct	s_var
{
	char			*name;
	int				name_len;
	char			*value;
	int				value_len;
	struct s_var	*next;
	struct s_var	*prev;
}				t_var;

typedef struct	s_env
{
	struct s_var	*head;
	struct s_var	*tail;
	int				size;
}				t_env;

t_var		*env_dlst_new(t_var *content);
void		env_dlst_append(t_env **env, t_var *new);
void		env_dlst_delcontent(t_var *var);
void		env_dlst_delnode(t_var *node, t_env **env);
void		env_dlst_clear(t_env **env);
void		env_dlst_update_value(char *name_value, char *name, t_env **env);

t_env		*init_env(char **env);
t_var		*prepare_env_content(char *env_var);
void		print_env(t_env *env);
void		unset_env_var(char *name, t_env **env);

void		export(char *name_value, t_env **env);

int			get_substr_len(char *s, char c);


#endif
