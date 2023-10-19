/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:56 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/19 16:26:55 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_printf.h"
# include "typedef.h"

#include <sys/types.h>
#include <dirent.h>

t_token	*create_node(void *content, int type);
t_token	*add_node_to_linked_list(t_token *head, void *content, int type);

// ------------------------------------------------------------------ EXPANSION
char	*build_str(char *old_str, t_list *var_lst);
char	*expansion(char *s, int exit_code);
void	del_var_lst(void *content);
void	print_var_lst(t_list *var_lst);

// -------------------------------------------------------------------- BULTINS
int		echo(char *s);
int		pwd(char *opt);
int		cd(char *path);

#endif
