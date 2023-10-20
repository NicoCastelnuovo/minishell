/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:56:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/20 16:05:02 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cc ./src/builtins/env.c ./src/builtins/main.c ./src/builtins/cd.c ./src/builtins/pwd.c -I./include/ -I./mylib/libft/ -I./mylib/ft_printf/ -I./mylib/get_next_line/ -L./mylib/ -lmylib
*/

/*
	TO DO:
	- Make a pre-check in case of a builtin, and throw error in case of args/option which should not be used.
*/

// --------- PWD ----------
// int	main(int argc, char **argv, char **env)
// {
// 	char	*opt0 = NULL;
// 	char	*opt1 = "-P";
// 	char	*opt2 = "";
// 	char	*opt3 = "        ";			// valid
// 	char	*opt4 = "\t\t    \n\n";		// valid
// 	char	*opt5 = "\t\t   !   \n\n";	// invalid

// 	char *wd = get_wd(NULL);
// 	ft_printf("Custom PWD: [%s]\n", wd);
// }

// --------- ENV ----------
// int	main(int argc, char **argv, char **env)
// {
// 	char	**env_cpy = copy_env(env);
// 	//try with empty environment

// 	print_env(env_cpy);

// 	return (0);
// }

// --------- CD ----------
// int	main(int argc, char **argv, char **env)
// {
// 	char	**env_cpy = copy_env(env);

// 	char	*path0 = "/";
// 	char	*path1 = "./";
// 	char	*path2 = "../";
// 	char	*path3 = "../libft";
// 	char	*path4 = "Where are you going?";
// 	char	*path5 = "/Users/ncasteln/Downloads";
// 	char	*path6 = "../../";

// 	ft_printf("BEFORE [%s]\n\n", get_env_var("PWD=", env_cpy));
// 	print_env(env_cpy);
// 	ft_printf("\n\n");
// 	if (cd("/", env_cpy))
// 		return (1);
// 	ft_printf("AFTER [%s]\n\n", get_env_var("PWD=", env_cpy));
// 	print_env(env_cpy);
// 	ft_printf("\n\n");
// 	return (0);
// }
