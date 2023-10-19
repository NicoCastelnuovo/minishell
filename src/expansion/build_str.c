/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:45:15 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/19 11:59:35 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_varname_len(t_list *var_lst)
{
	t_var	*var;
	int		len;

	len = 0;
	while (var_lst)
	{
		var = (t_var *)var_lst->content;
		if (var->name_len > 0)
			len += var->name_len + 1; // because of $ not counted in
		var_lst = var_lst->next;
	}
	return (len);
}

static int	get_varvalue_len(t_list *var_lst)
{
	t_var	*var;
	int		len;

	len = 0;
	while (var_lst)
	{
		var = (t_var *)var_lst->content;
		if (var->value_len > 0)
			len += var->value_len;
		var_lst = var_lst->next;
	}
	return (len);
}

int		get_total_len(t_list *var_lst, char *old_str)
{
	int		tot_varname_len;
	int		tot_varvalue_len;

	tot_varname_len = get_varname_len(var_lst);
	tot_varvalue_len = get_varvalue_len(var_lst);
	return (ft_strlen(old_str) - tot_varname_len + tot_varvalue_len);
}

static char	*create_new_str(t_list *var_lst, int total_len, char *old_str)
{
	char	*new_str;
	int		i;
	t_var	*var;

	new_str = ft_calloc(total_len + 1, sizeof(char)); // protect
	// new_str[total_len] = '\0'; // not necessary
	i = 0;
	while (i < total_len)
	{
		if (*old_str == '$' && var_lst)
		{
			var = (t_var *)var_lst->content;
			ft_strlcpy(new_str + i, var->value, var->value_len + 1);
			i += var->value_len;
			old_str += var->name_len + 1;
			var_lst = var_lst->next;
		}
		else
		{
			new_str[i] = *old_str;
			old_str++;
			i++;
		}
	}
	return (new_str);
}

char	*build_str(char *old_str, t_list *var_lst)
{
	int		total_len;
	char	*new_str;

	total_len = get_total_len(var_lst, old_str);
	new_str = create_new_str(var_lst, total_len, old_str);
	return (new_str);
}
