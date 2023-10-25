/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:56:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/25 10:17:43 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cc ./src/dlist/dlst_new.c ./src/dlist/dlst_delnode.c ./src/dlist/dlst_last.c ./src/dlist/dlst_append.c ./src/expansion/utils.c ./src/expansion/expansion.c ./src/expansion/build_str.c ./src/builtins/unset.c ./src/builtins/env.c ./src/builtins/main.c ./src/builtins/cd.c ./src/builtins/pwd.c -I./include/ -I./mylib/libft/ -I./mylib/ft_printf/ -I./mylib/get_next_line/ -L./mylib/ -lmylib
*/

/*
	TO DO:
	- Make a pre-check in case of a builtin, and throw error in case of args/option which should not be used.
	- Decide what to do in case of case to not handle (example 'cd <no argument provided>')
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
// 	// try with empty environment
// 	t_dlist	*env_cpy = init_env(env);
// 	print_env(env_cpy);

// 	return (0);
// }

// --------- CD ----------
// int	main(int argc, char **argv, char **env)
// {
// 	char	**env_cpy = init_env(env);

// 	char	*path0 = "/";
// 	char	*path1 = "./";
// 	char	*path2 = "../";
// 	char	*path3 = "../libft";
// 	char	*path4 = "Where are you going?";
// 	char	*path5 = "/Users/ncasteln/Downloads";
// 	char	*path6 = "../../";
// 	char	*path7 = "src";

// 	ft_printf("BEFORE [%s]\n\n", get_env_var_value("PWD=", &env_cpy));
// 	print_env(env_cpy);
// 	ft_printf("\n\n");
// 	if (cd(path5, env_cpy))
// 		return (1);
// 	ft_printf("AFTER [%s]\n\n", get_env_var_value("PWD=", &env_cpy));
// 	print_env(env_cpy);
// 	ft_printf("\n\n");
// 	return (0);
// }

// --------- UNSET ----------
int	main(int argc, char **argv, char **env)
{
	t_dlist	*env_cpy = init_env(env);
	print_env(env_cpy);

	unset_env_var("TERM_PROGRAM=", &env_cpy);
	unset_env_var("TERM=", &env_cpy);
	unset_env_var("HOMEBREW_TEMP=", &env_cpy);
	unset_env_var("SHELL=", &env_cpy);
	unset_env_var("TMPDIR=", &env_cpy);
	unset_env_var("TERM_PROGRAM_VERSION=", &env_cpy);
	unset_env_var("ORIGINAL_XDG_CURRENT_DESKTOP=", &env_cpy);
	unset_env_var("MallocNanoZone=", &env_cpy);
	unset_env_var("PATH=", &env_cpy);
	unset_env_var("SHLVL=", &env_cpy);
	unset_env_var("HOME=", &env_cpy);
	unset_env_var("LOGNAME=", &env_cpy);
	unset_env_var("PWD=", &env_cpy);
	unset_env_var("COLORTERM=", &env_cpy);
	unset_env_var("SECURITYSESSIONID=", &env_cpy);
	unset_env_var("_=", &env_cpy);
	unset_env_var("_=", &env_cpy);
	unset_env_var("COLORTERM=", &env_cpy);
	unset_env_var("SECURITYSESSIONID=", &env_cpy);
	unset_env_var("USER=", &env_cpy);
	unset_env_var("COMMAND_MODE=", &env_cpy);
	unset_env_var("VSCODE_GIT_ASKPASS_EXTRA_ARGS=", &env_cpy);
	unset_env_var("XPC_FLAGS=", &env_cpy);
	unset_env_var("XPC_SERVICE_NAME=", &env_cpy);
	unset_env_var("VSCODE_GIT_ASKPASS_MAIN=", &env_cpy);
	unset_env_var("HOMEBREW_CACHE=", &env_cpy);
	unset_env_var("LaunchInstanceID=", &env_cpy);
	unset_env_var("LANG=", &env_cpy);
	unset_env_var("VSCODE_GIT_IPC_HANDLE=", &env_cpy);
	unset_env_var("VSCODE_GIT_ASKPASS_NODE=", &env_cpy);
	unset_env_var("SSH_AUTH_SOCK=", &env_cpy);
	unset_env_var("__CF_USER_TEXT_ENCODING=", &env_cpy);
	unset_env_var("GIT_ASKPASS=", &env_cpy);

	// // no existing
	// unset_env_var("NO EXIST 0", &env_cpy);
	// unset_env_var("NO EXIST 1", &env_cpy);
	// unset_env_var("NO EXIST 2", &env_cpy);

	// // NULL
	// unset_env_var(NULL, &env_cpy);

	ft_printf("\n__ NEW ENV __\n");
	print_env(env_cpy);
	return (0);
}
