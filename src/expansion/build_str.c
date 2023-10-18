/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:45:15 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/18 18:44:08 by ncasteln         ###   ########.fr       */
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

char	*build_str(char *old_str, t_list *var_lst)
{
	int		tot_varname_len;
	int		tot_varvalue_len;
	int		total_len;

	ft_printf("OLD: [%s]\n", old_str);

	// get total size needed to allocate
	tot_varname_len = get_varname_len(var_lst);
	tot_varvalue_len = get_varvalue_len(var_lst);
	total_len = ft_strlen(old_str) - tot_varname_len + tot_varvalue_len; // \0 omitted
	ft_printf("OLD[%d] - VARNAME[%d] + VARVALUE[%d] + NULLTERM[1] = %d\n\n", ft_strlen(old_str), tot_varname_len, tot_varvalue_len, total_len + 1);

	// populate with characters
	char	*new_str;
	int		i;
	t_var	*var;

	new_str = ft_calloc(total_len + 1, sizeof(char)); // protect
	new_str[total_len] = '\0';
	i = 0;
	while (i < total_len)
	{
		if (*old_str != '$')
		{
			new_str[i] = *old_str;
			old_str++;
			i++;
		}
		else // substitution
		{
			var = (t_var *)var_lst->content;
			if (ft_strncmp(var->name, "$", ft_strlen(var->name)) == 0) // ,eams of it is $
			{
				// just copy it
				new_str[i] = *old_str;
				old_str++;
				i++;
			}
			else // need to explicitly handle not-existent variables ???
			{
				ft_strlcpy(new_str + i, var->value, var->value_len + 1);
				i += var->value_len;
				old_str += var->name_len + 1;
			}
			var_lst = var_lst->next;
		}
	}
	ft_printf("\nNEW STR: [%s]\n", new_str);
	ft_printf("\n");
	return (new_str);
}
