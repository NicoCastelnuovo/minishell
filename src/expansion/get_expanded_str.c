/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expanded_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:42:21 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/23 18:22:45 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	GET_VAR_NAME_LEN(char *s)
{
	char	*var_name;
	int		var_name_len;

	var_name = get_first_var_name(s); //allocates
	var_name_len = ft_strlen(var_name);
	free(var_name);
	return (var_name_len);
}

static char	*GET_VAR_VAL(char *s, t_list *env)
{
	char	*var_name;
	char	*var_value;

	var_name = get_first_var_name(s); //allocates
	if (get_env_custom(var_name, env))
		var_value = ft_strdup(get_env_custom(var_name, env));
	else
		var_value = ft_strdup("");
	return (var_value);
}

static int	copy_exit_code(char *new, char *old, int e_code, int *j)
{
	char	*tmp;

	tmp = ft_itoa(e_code); // protect
	if (!tmp)
		return (-1);
	ft_memcpy(new, tmp, ft_strlen(tmp));
	(*j) += ft_strlen(tmp);
	if (tmp)
		free(tmp);
	return (1);
}

static int	copy_env_var(char *new, char *old, int *j, int *i, t_list *env)
{
	char	*tmp;

	tmp = GET_VAR_VAL(old, env); // protect
	(*i) += GET_VAR_NAME_LEN(old);
	if (!tmp)
		return (-1);
	ft_memcpy(new, tmp, ft_strlen(tmp));
	(*j) += ft_strlen(tmp);
	if (tmp)
		free(tmp);
	return (1);
}

char	*get_expanded_str(char *s, int len, t_list *env, int e_code)
{
	char	*new;
	char	open_quote;
	int		is_open;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	open_quote = -1;
	is_open = 0;
	new = ft_calloc(len + 1, sizeof(char)); // protect
	if (!new)
		return (NULL);
	new[len] = '\0';
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$' && open_quote != TKN_S_QUOTE && i != ft_strlen(s) -1) // check terminating part of the string
		{
			if (s[i + 1] != TKN_S_QUOTE || s[i + 1] !=  TKN_D_QUOTE)
			{
				if (s[i + 1] == '$')
					new[j++] = s[i];
				else if (s[i + 1] == '?')
				{
					if (copy_exit_code(new + j, s, e_code, &j) == -1) // protect
						return (free(new), NULL);
					i++;
				}
				else
				{
					if (copy_env_var(new + j, s + i, &j, &i, env) == -1)
						return (free(new), NULL);
				}
			}

		}
		else //plain copy
		{
			change_open_quote_and_open(s[i], &is_open, &open_quote, NULL);
			new[j++] = s[i];
		}
		i++;
	}
	return (new);
}



				// tmp = GET_VAR_VAL(s + i, env); // protect
				// i += GET_VAR_NAME_LEN(s + i);
				// if (!tmp)
				// 	return (free(new), NULL);
				// ft_memcpy(new + j, tmp, ft_strlen(tmp));
				// j += ft_strlen(tmp);
				// if (tmp)
				// 	free(tmp);
