/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mid_step.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:08:27 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/24 15:13:48 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_is_open_quote(char curr_quote, char *is_open, int *len)
{
	if (*is_open == -1)	// quotes are closed
	{
		(*is_open) = curr_quote;
	}
	else // quote are open
	{
		if ((*is_open) == curr_quote)
			(*is_open) = -1;
	}
	if (len)
		(*len)++;
}

static char	*mid_copy(char *old, int len)
{
	int		i;
	int		j;
	char	is_open;
	char	*mid_str;

	mid_str = ft_calloc(len, sizeof(char)); // protect
	mid_str[len] = '\0';
	is_open = -1;
	i = 0;
	j = 0;
	while (old[i])
	{
		if (old[i] == '$' && is_open == -1 && (old[i + 1] == TKN_S_QUOTE || old[i + 1] == TKN_D_QUOTE))
				i++;
		if (old[i] == TKN_S_QUOTE || old[i] == TKN_D_QUOTE)
			change_is_open_quote(old[i], &is_open, NULL);
		mid_str[j] = old[i];
		j++;
		i++;
	}
	return (mid_str);
}

int	remove_dollar_followed_by_quotes(char *old)
{
	int		len;
	int		i;
	char	is_open;

	is_open = -1;
	len = 0;
	i = 0;
	while (old[i])
	{
		if (old[i] == '$' && is_open == -1) // case not to count
		{
			if (old[i + 1] == TKN_S_QUOTE || old[i + 1] == TKN_D_QUOTE)
				i++;
			else
			{
				len++;
				i++;
			}
		}
		if (old[i] == TKN_S_QUOTE || old[i] == TKN_D_QUOTE)
			change_is_open_quote(old[i], &is_open, NULL);
		len++;
		i++;
	}
	return (len);
}

/*
	In this mid_step of expansion, all the unuseful $ sign are removed, such as
	$"" and $'' to make the next steps of expansion easier to handle.
*/
char *mid_step(char *old_str)
{
	int		len;
	char	*mid_str;

	len = remove_dollar_followed_by_quotes(old_str);
	mid_str = mid_copy(old_str, len);
	return (mid_str);
}
