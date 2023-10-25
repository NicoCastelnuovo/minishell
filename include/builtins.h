/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:54:01 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/25 14:56:58 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

const char	*get_wd(char *opt);
int			cd(char *path, char **env);


// void		update_env_var(char *name, char *value, char **env);
// t_var		*search_var(char *name, t_list *env);

#endif
