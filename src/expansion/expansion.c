/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:18:55 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/18 18:43:04 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cc ./src/expansion/expansion.c ./src/expansion/build_str.c -I./include/ -I./mylib/libft/ -I./mylib/ft_printf/ -I./mylib/get_next_line/ -L./mylib/libft -lft -L./mylib/ft_printf/ -lftprintf
*/

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

/*
	For each variable name in the list, getenv() is applied, and the value is
	duplicated into the node. If the variable doesn't exist, an empty string
	is duplicated.
*/
static void	expand_variables(t_list *var_lst, int n, int exit_code)
{
	char	*expanded;
	t_var	*var;

	while (var_lst) // check if ok not createing a cpy
	{
		var = (t_var *)var_lst->content;
		if (ft_strncmp(var->name, "$", 1) != 0) // if not the dollar sign, need to expand otherwise not
		{
			if (ft_strncmp(var->name, "?", 1) == 0)
				expanded = ft_itoa(exit_code);
			else
				expanded = getenv(var->name);
			if (!expanded)
			{
				var->value = ft_strdup("");
				var->value_len = ft_strlen(var->value);
			}
			else
			{
				var->value = ft_strdup(expanded);
				var->value_len = ft_strlen(var->value);
			}
		}
		// else if (ft_strncmp(var->name, "?", 1)) ------> !!!!
		var_lst = var_lst->next; // check if ok not createing a cpy
	}
	ft_printf("\n");
}

/*
	Based on the number of $ sign found in the string, the function returns
	a list whose content has the variable name to expand, and the length of it.
*/
static t_list	*create_varlst(char *s, int n)
{
	t_list	*var_lst;
	t_list	*new_node;
	t_var	*var;
	int		i;

	var_lst = NULL;
	i = 0;
	while (i < n)
	{
		var = ft_calloc(1, sizeof(t_var)); // protect
		s = ft_strchr(s, '$');
		s++;
		var->name_len = get_var_name_len(s);
		if (var->name_len == 0)
			var->name = ft_strdup("$"); // better allocate or not ???
		else
			var->name = ft_substr(s, 0, var->name_len);
		var->value = NULL;
		var->value_len = -1;
		new_node = ft_lstnew(var);
		// protect
		ft_lstadd_back(&var_lst, new_node);
		i++;
	}
	return (var_lst);
}

static char **expansion(char *s, int exit_code)
{
	int		n;
	t_list	*var_lst;
	char	*new_string;

	n = get_n_dollars(s);
	var_lst = create_varlst(s, n);
	expand_variables(var_lst, n, exit_code);
	t_list *head = var_lst;


	while (head)
	{
		if (head->content)
		{
			ft_printf("name [%s]", ((t_var *)head->content)->name);
			ft_printf("[%d]\n", ((t_var *)head->content)->name_len);
			ft_printf("value [%s]", ((t_var *)head->content)->value);
			ft_printf("[%d]\n", ((t_var *)head->content)->value_len);
		}
		head = head->next;
	}
	ft_printf("________\n\n");


	new_string = build_str(s, var_lst);

}

int main(int argc, char **argv, char **env)
{
	char	*s0 = "This is $USER and other shit"; 			// ---> ncasteln and other shit
	char	*s1 = "$USERHELLO";								// ---> []
	char	*s2 = "USER$?USER"; 							// ---> USER0USER
	char	*s3 = "$USER $PWD"; 							// ---> ncastelnncasteln
	char	*s4 = "$USER?";									// ncasteln?
	char	*s5 = "I am $USER I am in $PWD, I've got a lot of $";
	char	*s6 = "--> $ <--";
	char	*s7 = "$$$ $ $ $USER$$$$$";
	char	*s8 = "$NOTEXIST";
	char	*s9 = "$! $@ $# $$ $% $^ $& $* $( $) $_ $+ $:";
	char	*s10 = "Hello $USER$NOTHING$!!!";
	char	*s11 = "$PWD$";
	char	*s12 = "     $WTF    ";							// [9 blank spaces]
	char	*s13 = "Hello my name is $USER and my last command was $_";							// [9 blank spaces]
	char	*s14 = "$USER$?$USER"; 							// ---> ncasteln99ncasteln

	char	**to_expand;

	// to_expand = expansion(s0, 0);
	// to_expand = expansion(s1, 0);
	// to_expand = expansion(s2, 0);
	// to_expand = expansion(s3, 0);
	// to_expand = expansion(s4, 0);
	// to_expand = expansion(s5, 0);
	// to_expand = expansion(s6, 0);
	// to_expand = expansion(s7, 0);
	// to_expand = expansion(s8, 0);
	to_expand = expansion(s9, 0);
	// to_expand = expansion(s10, 0);
	// to_expand = expansion(s11, 0);
	// to_expand = expansion(s12, 0);
	// to_expand = expansion(s13, 0);
	// to_expand = expansion(s14, 99);


}
