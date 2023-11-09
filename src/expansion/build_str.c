/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:49:20 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/09 18:02:56 by ncasteln         ###   ########.fr       */
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

static char	*trim_quotes(char *s)
{
	char	*new;
	int		old_len;
	int		i;
	int		j;

	old_len = ft_strlen(s);
	new = ft_calloc(ft_strlen(s) - 2, sizeof(char)); //protect
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i == 0 || i == old_len - 1)
			i++;
		else
		{
			new[j] = s[i];
			j++;
			i++;
		}
	}
	return (new);
}

static int	get_total_len(t_list *var_lst, char *old_str)
{
	int		tot_varname_len;
	int		tot_varvalue_len;

	tot_varname_len = get_varname_len(var_lst);
	tot_varvalue_len = get_varvalue_len(var_lst);
	if (old_str[0] == TKN_D_QUOTE || old_str[1] == TKN_S_QUOTE)
		return (ft_strlen(old_str) - tot_varname_len + tot_varvalue_len - 2);
	return (ft_strlen(old_str) - tot_varname_len + tot_varvalue_len);
}

static char	*create_new_str(t_list *var_lst, int total_len, char *old_str)
{
	char	*new_str;
	int		i;
	t_var	*var;
	char	*tmp;

	new_str = ft_calloc(total_len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	ft_printf("OLDSTRING {{{{{%s}}}}}\n", old_str);
	ft_printf("TOTAL LEN {{{{{%d}}}}}\n", total_len);
	if (old_str[0] == TKN_D_QUOTE || old_str[1] == TKN_S_QUOTE)
	{
		tmp = old_str;
		old_str = trim_quotes(old_str);
		ft_printf("old trimmed {{{%s}}}\n", old_str);
		// free(tmp);
	}
	while (i < total_len)
	{
		if (*old_str == '$' && var_lst)
		{
			var = (t_var *)var_lst->content;
			ft_strlcpy(new_str + i, var->value, var->value_len + 1);
			ft_printf("VAR VALUE = [%s]\n", var->value);
			i += var->value_len;
			// if (ft_strncmp(new_str, "$", ft_strlen(new_str)) == 0)
			// 	old_str += 1;
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


/*
	$USER      !
	ncasteln      !
*/
