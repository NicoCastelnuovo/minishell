/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:44:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/24 14:52:44 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_var_value_len(char *s, t_list *env)
{
	int		i;
	char	*name;
	int		len;
	char	*value;

	i = 1;
	len = 0;
	ft_printf("I RECIEVE [%s]\n", s); // $USER
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	name = ft_substr(s, 1, i - 1);
	ft_printf("NAME[%s]\n", name);
	value = get_env_custom(name, env);
	ft_printf("VALUE[%s]\n", value);
	if (value)
		len = ft_strlen(name);
	free(name);
	ft_printf("ADD LEN [%d]\n", len);
	return (len);
}

/*
	Search the first possible variable name considering that the valid char
	are alphanum and underscore, returning its length.
*/
static int	get_first_possible_var_name_len(char *s)
{
	int		i;

	i = 1;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	ft_printf("MOVE i [%d] times\n", i);
	return (i); // no +1 because at every cyce is done
}

int	get_len_with_env_var_expanded(char *s, t_list *env, t_list **store_var)
{
	int		len;
	int		i;
	char	is_open;

	is_open = -1;
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '$' && (ft_isalnum(s[i + 1]) || s[i] == '_') && is_open != TKN_S_QUOTE)
		{
			len += get_var_value_len(s + i, env);
			i += get_first_possible_var_name_len(s + i); // jump
			ft_printf("JUMP to [%c]\n", s[i + 1]);
		}
		else if (s[i] == '$' && (ft_isalnum(s[i + 1]) || s[i] == '_') && is_open == TKN_S_QUOTE)
			len++;
		else
		{
			if (s[i] == TKN_S_QUOTE || s[i] == TKN_D_QUOTE)
				change_is_open_quote(s[i], &is_open, NULL);
			len++;
		}
		i++;
	}
	ft_printf("LEN = [%d]\n", len);
	return (len);
}

char	*expand_variables(char *old, t_list *env)
{
	int		len;
	char	*new;
	t_list	*store_var;

	len = get_len_with_env_var_expanded(old, env, &store_var);
	// new = copy_with_variables()
	exit(1);
	return (new);
}
