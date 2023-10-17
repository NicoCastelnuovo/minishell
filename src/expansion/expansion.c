/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:18:55 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/17 17:30:20 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cc ./src/expansion/expansion.c -I./include/ -I./mylib/libft/ -I./mylib/ft_printf/ -I./mylib/get_next_line/ -L./mylib/libft -lft -L./mylib/ft_printf/ -lftprintf
*/

static char *substitute(char *env_var)
{
	char *value;

	if (ft_strlen(env_var) == 1 && env_var[0] == '?')
		return ("--- exit_code ---");
	value = getenv(env_var);
	if (!value)
		return ("");
	return (value);
}

/*
	Take as argument a string without dollar sign included.
*/
static int	get_var_name_len(char *s)
{
	int	i;

	if (s[0] == '?')
		return (1);
	i = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

static int	get_n_dollars(char *s)
{
	int	n;

	n = 0;
	while (*s)
	{
		if (*s == '$')
			n++;
		s++;
	}
	return (n);
}

static void expand_variables(char **to_expand, int n)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < n)
	{
		if (to_expand[i])
		{
			// tmp = to_expand[i];
			// free(to_expand[i]);
			// if (ft_strncmp(tmp, "?", 1) == 0)
			// 	to_expand[i] = ft_strdup("?");
			// else
			// {
			// 	to_expand[i] = getenv(tmp); // not good, duplicates
			// 	// if (!to_expand[i])
			// 	// 	to_expand[i] = ft_strdup(" ");
			// }
		}
		ft_printf("[%s]\n", to_expand[i]);
		i++;
	}
	ft_printf("\n");
}

static char **get_env_var_names(char *s, int n)
{
	char	**to_expand;
	int		i;
	int		len;

	to_expand = ft_calloc(n + 1, sizeof(char *));
	if (!to_expand)
		return (NULL);
	to_expand[n] = NULL;


	i = 0;
	while (i < n)
	{
		s = ft_strchr(s, '$');
		s++;
		len = get_var_name_len(s);
		if (len == 0)
			to_expand[i] = "$"; // better $
		else
			to_expand[i] = ft_substr(s, 0, len);
		i++;
	}
	return (to_expand);
}

static char **expansion(char *s)
{
	int		n;
	char	**to_expand;

	n = get_n_dollars(s);
	to_expand = get_env_var_names(s, n);
	expand_variables(to_expand, n);
}

int main(int argc, char **argv, char **env)
{
	char	*s0 = "This is $USER and other shit"; 				// ---> ncasteln and other shit
	char	*s1 = "$USERHELLO";			// ---> []
	char	*s2 = "USER$?USER"; 		// ---> USER0USER
	char	*s3 = "$USER$PWD"; 		// ---> ncastelnncasteln
	char	*s4 = "$USER?";				// ncasteln?
	char	*s5 = "I am $USER I am in $PWD, I've got a lot of $";
	char	*s6 = "--> $ <--";			// ---> nothing to store
	char	*s7 = "$$$ $ $ $PWD $ $ $$$";			// ---> nothing to store
	char	*s8 = "$NOTEXIST";

	char	**to_expand;

	to_expand = expansion(s0);
	to_expand = expansion(s1);
	to_expand = expansion(s2);
	to_expand = expansion(s3);
	to_expand = expansion(s4);
	to_expand = expansion(s5);
	to_expand = expansion(s6);
	to_expand = expansion(s7);
	to_expand = expansion(s8);
}





		// s = ft_strchr(s, '$');
		// s++;
		// if (s[0] == '?')
		// 	to_expand[i] = ft_strdup("?");
		// else
		// {
		// 	len = get_var_name_len(s);
		// 	ft_printf("len = %d\n", len);
		// 	if (len == 0)
		// 		to_expand[i] = ft_strdup("$");
		// 	else
		// 		to_expand[i] = ft_substr(s, 0, len);
		// 	// if (!to_expand)
		// 	ft_printf("[%s]\n", to_expand[i]);
		// }
		// i++;
