/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_e_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:47:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/24 12:42:35 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_with_e_code(char *s, int len, char *e_code_str)
{
	int		i;
	int		j;
	char	*new;
	char	is_open;

	i = 0;
	j = 0;
	is_open = -1;
	new = ft_calloc(len + 1, sizeof(char)); // protect
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (s[i + 1] == '?' && is_open != TKN_S_QUOTE)
			{
				ft_memcpy(new + j, e_code_str, ft_strlen(e_code_str));
				j += ft_strlen(e_code_str);
				i++;
			}
		}
		else
		{
			if (s[i] == TKN_S_QUOTE || s[i] == TKN_D_QUOTE)
				change_is_open_quote(s[i], &is_open, NULL);
			new[j] = s[i];
			j++;
		}
		i++;
	}
	return (new);
}

static int	get_len_with_e_code_expanded(char *s, char *e_code_str)
{
	int		len;
	int		i;
	char	is_open;

	is_open = -1;
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (s[i + 1] == '?' && is_open != TKN_S_QUOTE)
			{
				len += ft_strlen(e_code_str);// protect
				i++;
			}
		}
		else
		{
			if (s[i] == TKN_S_QUOTE || s[i] == TKN_D_QUOTE)
				change_is_open_quote(s[i], &is_open, NULL);
			len++;
		}
		i++;
	}
	return (len);
}

char	*expand_e_code(char *old, int e_code)
{
	int		len;
	char	*new;
	char	*e_code_str;

	e_code_str = ft_itoa(e_code); // protect
	len = get_len_with_e_code_expanded(old, e_code_str);
	new = copy_with_e_code(old, len, e_code_str);
	return (new);
}


		// if (old[i] == '$' && is_open == -1) // case not to count
		// {
		// 	if (old[i + 1] == TKN_S_QUOTE || old[i + 1] == TKN_D_QUOTE)
		// 		i++;
		// 	else
		// 	{
		// 		len++;
		// 		i++;
		// 	}
		// }
		// if (old[i] == TKN_S_QUOTE || old[i] == TKN_D_QUOTE)
		// 	change_is_open_quote(old[i], &is_open, NULL);
		// len++;
		// i++;
