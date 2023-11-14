/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 08:28:29 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/*
	NOTES and STUFF TO DO:
	• EXPORT
		- Still need to order as ASCII char
		- multiple args handling
		- Each node maybe need a boolean which signs as exportable or non-exportable (and change init_env)
	• ENV
		- Verify with empty env, or decide what happend in case there is nothing - env_cpy still exist?
		- Pay attention on whatsend to child ps
		- Everytime a cmd is executed set $_ except if pipechain
		- Where the fuck is user
	• UNSET
		- make VARNAME= not a valid input
		- multiple args handling
*/

typedef struct	s_var
{
	char	*name;
	int		name_len;
	char	*value;
	int		value_len;
	int		to_export;
}				t_var;

typedef struct	s_env
{
	struct s_var	*head; // remove
	struct s_var	*tail;
	int				size;
}				t_env;

// ------------------------------------------------------------------------ ENV
t_list	*init_env(char **env);
t_var	*create_var_content(char *env_var);
void	del_var_content(void *content);
char	*get_env_custom(char *name, t_list *env);

#endif
