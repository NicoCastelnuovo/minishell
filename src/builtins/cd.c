/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:20:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/11 16:50:51 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_wd(void)
{
	char	*buff;
	size_t	size;

	buff = NULL;
	size = 1;
	buff = ft_calloc(size + 1, sizeof(char)); // protect --- create err function!
	buff = getcwd(buff, size);
	while (!buff)
	{
		free(buff);
		size += 1;
		buff = ft_calloc(size + 1, sizeof(char)); // protect --- create err function
		buff = getcwd(buff, size);
	}
	return (buff);
}

/*
	Updates both PWD and OLDPWD variables, depending on the name passed in.
*/
// static void	update_pwd_var(t_env *env, char *name)
// {
// 	t_var	*new_var;
// 	char	*abs_path; // change fucntion to be more general ????

// 	abs_path = get_wd();
// 	new_var = ft_calloc(1, sizeof(t_var)); // protect
// 	new_var->name = ft_strdup(name);
// 	new_var->name_len = ft_strlen(new_var->name);
// 	new_var->value = abs_path;
// 	new_var->value_len = ft_strlen(new_var->value);
// 	new_var->to_export = 1; // change
// 	env_dlst_update(new_var, &env);
// }

/*
	cd changes the current working directory of the current shell env. Only a
	relative or an absolute path are accepted.
*/
void	cd(t_data *data)
{
	char	*to_path;
	char	*abs_path;
	char	*key_value;
	t_var	*new;

	// abs_path = get_wd();
	// key_value = ft_strjoin("OLDPWD=", abs_path);
	// if (abs_path)
	// 	free(abs_path);
	// new = env_dlst_new(key_value);
	// env_dlst_update(new, &data->env);

	// ---------------------------------------------

	to_path = ((t_cmd *)data->tree->content)->args[1];
	// if (ft_strcmp(to_path, "") == 0)
	// {
	// 	ft_printf("-----------GO TO ROOOOOOT -------------\n");
	// }
	if (chdir(to_path) == -1)
		data->e_code = errno; // print error
	else
	{
		abs_path = get_wd();
		key_value = ft_strjoin("PWD=", abs_path);
		if (abs_path)
			free(abs_path);
		new = env_dlst_new(key_value);
		env_dlst_update(new, &data->env);
	}
}
