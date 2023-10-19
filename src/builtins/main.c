/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:56:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/19 12:59:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cc ./src/builtins/main.c ./src/builtins/pwd.c -I./include/ -I./mylib/libft/ -I./mylib/ft_printf/ -I./mylib/get_next_line/ -L./mylib/ -lmylib
*/

int	main(int argc, char **argv, char **env)
{
	char	*opt0 = NULL;
	char	*opt1 = "-P";
	char	*opt2 = "";
	char	*opt3 = "        ";			// valid
	char	*opt4 = "\t\t    \n\n";		// valid
	char	*opt5 = "\t\t   !   \n\n";	// invalid

	if (pwd(opt0))
		return (1);
	return (0);
}
