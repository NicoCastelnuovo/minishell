/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_total_new_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:36:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/24 10:12:02 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_first_var_name(char *s) // like $USERabcd or $USER+abcd or $SHIT!!!
{
	int	i;
	char	*var_name;

	i = 1;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	var_name = ft_calloc(i + 1, sizeof(char)); // protect
	ft_strlcpy(var_name, s + 1, i);
	return (var_name);
}

void	change_open_quote_and_open(char curr_quote, int *is_open, char *open_quote, int *len)
{
	// try to change no using is_open but jut open_quote
	if (!(*is_open))
	{
		(*is_open) = 1;
		(*open_quote) = curr_quote;
	}
	else
	{
		if ((*open_quote) == curr_quote)
		{
			(*is_open) = 0;
			(*open_quote) = -1;
		}
	}
	if (len) //added to reuse the funciton in 2 contexts
		(*len)++;
}

static int	add_var_value_len(char *s, t_list *env, int *len)
{
	char	*var_name;
	int		var_name_len;
	char	*var_value;
	int		var_value_len;

	var_value_len = 0;
	var_name = get_first_var_name(s); //allocates
	var_name_len = ft_strlen(var_name);
	var_value = get_env_custom(var_name, env);
	if (var_value)
		var_value_len = ft_strlen(var_value);
	(*len) += var_value_len;
	return (var_name_len);
}

static int	get_expanded_length(char *s, int i, int *len, t_data *data)
{
	int	var_name_len;

	var_name_len = 0;
	if (s[i + 1] == '$')
		(*len)++;
	else if (s[i + 1] == '?')
	{
		(*len) += ft_strlen(ft_itoa(data->e_code)); // protect
		return (1);
	}
	else
	{
		var_name_len = add_var_value_len(s + i, data->env, len); // protect ?
		return (var_name_len);
	}
	return (0);
}

int	get_total_new_len(char *s, t_data *data)
{
	int		i;
	int		len;
	char	open_quote;
	int		is_open = -1;

	i = 0;
	len = 0;
	open_quote = -1;
	while (s[i])
	{
		if (s[i] == '$') // check terminating part of the string
		{
			if (s[i + 1] != TKN_S_QUOTE && s[i + 1] != TKN_S_QUOTE)
				i += get_expanded_length(s, i, &len, data);
		}
		else
		{
			if (s[i] == TKN_S_QUOTE || s[i] == TKN_D_QUOTE)
				change_open_quote_and_open(s[i], &is_open, &open_quote, &len);
			else
				len++;
		}
		i++;
	}
	return (len);
}




// char	*get_first_var_name(char *s) // like $USERabcd or $USER+abcd or $SHIT!!!
// {
// 	int	i;
// 	char	*var_name;

// 	i = 1;
// 	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
// 		i++;
// 	var_name = ft_calloc(i + 1, sizeof(char)); // protect
// 	ft_strlcpy(var_name, s + 1, i);
// 	return (var_name);
// }

// void	change_open_quote_and_open(char curr_quote, int *is_open, char *open_quote, int *len)
// {
// 	// try to change no using is_open but jut open_quote
// 	if (!(*is_open))
// 	{
// 		(*is_open) = 1;
// 		(*open_quote) = curr_quote;
// 	}
// 	else
// 	{
// 		if ((*open_quote) == curr_quote)
// 		{
// 			(*is_open) = 0;
// 			(*open_quote) = -1;
// 		}
// 	}
// 	if (len) //added to reuse the funciton in 2 contexts
// 		(*len)++;
// }

// static int	add_var_value_len(char *s, t_list *env, int *len)
// {
// 	char	*var_name;
// 	int		var_name_len;
// 	char	*var_value;
// 	int		var_value_len;

// 	var_value_len = 0;
// 	var_name = get_first_var_name(s); //allocates
// 	var_name_len = ft_strlen(var_name);
// 	var_value = get_env_custom(var_name, env);
// 	if (var_value)
// 		var_value_len = ft_strlen(var_value);
// 	(*len) += var_value_len;
// 	return (var_name_len);
// }

// static int	handle_dollar_exit_code(char *s, int i, int *len, int e_code)
// {
// 	if (s[i + 1] == '?')
// 	{
// 		(*len) += ft_strlen(ft_itoa(e_code));
// 		return (1);
// 	}
// 	return (0);
// }

// static int	handle_dollar_sign_and_var(char *s, int i, int *len, t_list *env)
// {
// 	int	var_name_len;

// 	var_name_len = 0;

// 	if (s[i + 1] == '$')
// 		(*len)++;
// 	else
// 	{
// 		var_name_len = add_var_value_len(s + i, env, len); // protect ?
// 		return (var_name_len);
// 	}
// 	return (0);
// }

// int	get_total_new_len(char *s, t_list *env, int e_code)
// {
// 	int		i;
// 	int		len;
// 	char	open_quote;
// 	int		is_open;

// 	i = 0;
// 	len = 0;
// 	open_quote = -1;
// 	is_open = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '$') // check terminating part of the string
// 		{
// 			if (s[i + 1] != TKN_S_QUOTE && s[i + 1] != TKN_S_QUOTE)
// 			{
// 				i += handle_dollar_sign_and_var(s, i, &len, env);
// 				i += handle_dollar_exit_code(s, i, &len, e_code);
// 			}
// 		}
// 		else
// 		{
// 			if (s[i] == TKN_S_QUOTE || s[i] == TKN_D_QUOTE)
// 				change_open_quote_and_open(s[i], &is_open, &open_quote, &len);
// 			else
// 				len++;
// 		}
// 		i++;
// 	}
// 	return (len);
// }
