/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:56:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/20 12:50:10 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cc ./src/utils/copy_envp.c ./src/builtins/main.c ./src/builtins/print_env.c ./src/builtins/cd.c ./src/builtins/pwd.c -I./include/ -I./mylib/libft/ -I./mylib/ft_printf/ -I./mylib/get_next_line/ -L./mylib/ -lmylib
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

// 	if (pwd(opt0))
// 		return (1);
// 	return (0);
// }

// --------- CD ----------
int	main(int argc, char **argv, char **envp)
{
	char	*path0 = "/";
	char	*path1 = "./";
	char	*path2 = "../";
	char	*path3 = "../libft";
	char	*path4 = "Where are you going?";
	char	*path5 = "/Users/ncasteln/Downloads";
	char	*path6 = "../../";

	char	**envp_cpy = copy_envp(envp);

	// if (cd(path6, env))
	// 	return (1);
	return (0);
}
