/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:18:55 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/18 13:52:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cc ./src/expansion/expansion.c -I./include/ -I./mylib/libft/ -I./mylib/ft_printf/ -I./mylib/get_next_line/ -L./mylib/libft -lft -L./mylib/ft_printf/ -lftprintf
*/

static char *build_new_string(char *src, char **expanded, int total_var_len)
{
	char	*new_string;
	int		total_len;
	int		i;


}

/*
	Take as argument a string without dollar sign included. It checks
	immediately if the parameter is $?, which is not an env var, but a Shell
	built-in variable.
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

static int expand_variables(char **to_expand, int n)
{
	char	*tmp;
	char	*expanded;
	int		i;
	int		total_var_len;

	total_var_len = 0;
	i = 0;
	while (i < n)
	{
		ft_printf("[%s] -> ", to_expand[i]);
		if (ft_strncmp(to_expand[i], "$", 1)) // if not the dollar sign, need to expand otherwise not
		{
			total_var_len += ft_strlen(to_expand[i] + 1);
			expanded = getenv(to_expand[i]);
			tmp = to_expand[i];
			if (!expanded)
				to_expand[i] = ft_strdup("");
			else
				to_expand[i] = ft_strdup(expanded);
			free(tmp);
		}
		ft_printf("[%s]\n", to_expand[i]);
		i++;
	}
	ft_printf("\n");
	return (total_var_len);
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
	int		total_var_len;
	char	**to_expand;
	char	*expanded_string;

	n = get_n_dollars(s);
	to_expand = get_env_var_names(s, n);
	total_var_len = expand_variables(to_expand, n);
	// to_expand are now expanded
	expanded_string = build_new_string(s, to_expand, total_var_len);
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
	char	*s7 = "$$$ $ $ $PWD$";			// ---> nothing to store
	char	*s8 = "$NOTEXIST";
	char	*s9 = "$! $@ $# $$ $% $^ $& $* $( $) $_ $+ $:";

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
	to_expand = expansion(s9);


}







// 	cc ./src/expansion/expansion.c -I./include/ -I./mylib/libft/ -I./mylib/ft_printf/ -I./mylib/get_next_line/ -L./mylib/libft -lft -L./mylib/ft_printf/ -lftprintf
// */

// static char *build_new_string(char *src, char **expanded, int total_var_len)
// {
// 	char	*new_string;
// 	int		total_len;
// 	int		i;


// }

// /*
// 	Take as argument a string without dollar sign included. It checks
// 	immediately if the parameter is $?, which is not an env var, but a Shell
// 	built-in variable.
// */
// static int	get_var_name_len(char *s)
// {
// 	int	i;

// 	if (s[0] == '?')
// 		return (1);
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (!ft_isalnum(s[i]) && s[i] != '_')
// 			return (i);
// 		i++;
// 	}
// 	return (i);
// }

// static int	get_n_dollars(char *s)
// {
// 	int	n;

// 	n = 0;
// 	while (*s)
// 	{
// 		if (*s == '$')
// 			n++;
// 		s++;
// 	}
// 	return (n);
// }

// static int expand_variables(char **to_expand, int n)
// {
// 	char	*tmp;
// 	char	*expanded;
// 	int		i;
// 	int		total_var_len;

// 	total_var_len = 0;
// 	i = 0;
// 	while (i < n)
// 	{
// 		ft_printf("[%s] -> ", to_expand[i]);
// 		if (ft_strncmp(to_expand[i], "$", 1)) // if not the dollar sign, need to expand otherwise not
// 		{
// 			total_var_len += ft_strlen(to_expand[i] + 1);
// 			expanded = getenv(to_expand[i]);
// 			tmp = to_expand[i];
// 			if (!expanded)
// 				to_expand[i] = ft_strdup("");
// 			else
// 				to_expand[i] = ft_strdup(expanded);
// 			free(tmp);
// 		}
// 		ft_printf("[%s]\n", to_expand[i]);
// 		i++;
// 	}
// 	ft_printf("\n");
// 	return (total_var_len);
// }

// static t_list	*get_env_var_names(char *s, int n)
// {
// 	t_list	*env_lst;
// 	t_list	*new_node;
// 	t_var	*content;
// 	int		i;

// 	env_lst = ft_calloc(1, sizeof(t_list));
// 	i = 0;
// 	while (i < n)
// 	{
// 		content = ft_calloc(1, sizeof(t_var)); // protect
// 		s = ft_strchr(s, '$');
// 		s++;
// 		content->len = get_var_name_len(s);
// 		if (content->len == 0)
// 			content->var = ft_strdup("$"); // better allocate or not ???
// 		else
// 			content->var = ft_substr(s, 0, content->len);
// 		new_node = ft_lstnew((t_var *) content);
// 		ft_lstadd_back(&env_lst, new_node);
// 		i++;
// 	}
// 	return (env_lst);
// }

// static char **expansion(char *s)
// {
// 	int		n;
// 	t_list	*env_lst;

// 	n = get_n_dollars(s);
// 	env_lst = get_env_var_names(s, n);

// 	ft_printf("var [%s] len of [%d]\n", ((t_var *)head->content)->var, 1);
// 	// t_list *head = env_lst;
// 	// while (head->next)
// 	// {
// 	// 	head = head->next;
// 	// }
// }

// int main(int argc, char **argv, char **env)
// {
// 	char	*s0 = "This is $USER and other shit"; 				// ---> ncasteln and other shit
// 	char	*s1 = "$USERHELLO";			// ---> []
// 	char	*s2 = "USER$?USER"; 		// ---> USER0USER
// 	char	*s3 = "$USER$PWD"; 		// ---> ncastelnncasteln
// 	char	*s4 = "$USER?";				// ncasteln?
// 	char	*s5 = "I am $USER I am in $PWD, I've got a lot of $";
// 	char	*s6 = "--> $ <--";			// ---> nothing to store
// 	char	*s7 = "$$$ $ $ $PWD$";			// ---> nothing to store
// 	char	*s8 = "$NOTEXIST";
// 	char	*s9 = "$! $@ $# $$ $% $^ $& $* $( $) $_ $+ $:";

// 	char	**to_expand;

// 	to_expand = expansion(s0);
// 	to_expand = expansion(s1);
// 	to_expand = expansion(s2);
// 	to_expand = expansion(s3);
// 	to_expand = expansion(s4);
// 	to_expand = expansion(s5);
// 	to_expand = expansion(s6);
// 	to_expand = expansion(s7);
// 	to_expand = expansion(s8);
// 	to_expand = expansion(s9);


// }





// 		// s = ft_strchr(s, '$');
// 		// s++;
// 		// if (s[0] == '?')
// 		// 	to_expand[i] = ft_strdup("?");
// 		// else
// 		// {
// 		// 	len = get_var_name_len(s);
// 		// 	ft_printf("len = %d\n", len);
// 		// 	if (len == 0)
// 		// 		to_expand[i] = ft_strdup("$");
// 		// 	else
// 		// 		to_expand[i] = ft_substr(s, 0, len);
// 		// 	// if (!to_expand)
// 		// 	ft_printf("[%s]\n", to_expand[i]);
// 		// }
// 		// i++;
