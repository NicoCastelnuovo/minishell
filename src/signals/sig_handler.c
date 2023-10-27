/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:35:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/27 17:10:33 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_exit(int sig_n)
{
	ft_printf("Exit\n");
}

static void	handle_new_line(int sig_n)
{
	ft_printf("New line!\n");
	exit(1) ;
}

static void	handle_nothing(int sig_n)
{
	ft_printf("Hello signals\n");
}

void	init_sig_handling(void)
{
	struct sigaction	nl;
	int				i;

	nl.sa_handler = &handle_new_line;
	sigaction(SIGINT, &nl, NULL);
}
