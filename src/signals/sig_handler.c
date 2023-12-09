/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:35:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 17:44:04 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_num = 0;

/*
	SIGINT prints a new line.
	@line	rl_on_new_line() - tell the program to move to a new line
	@line	rl_redisplay() - update what is displayed, to reflect the buffer
*/
static void	handle_sa_newline(int sig_n)
{
	(void)sig_n;
	g_sig_num = 1;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	// printf("HANDLED\n");
}

/* void	configs()
{
	struct termios	config;

	tcgetattr(0, &config);
	config.c_cflag &= ~ECHOCTL;
	tcsetattr(0, 0, &config);
} */

void	init_sig_handling(void)
{
	struct sigaction	sa_newline;
	struct sigaction	sa_ignore;
	sigset_t			set;

	// configs();
	ft_bzero(&sa_newline, sizeof(sa_newline));
	ft_bzero(&sa_ignore, sizeof(sa_ignore));
	sigemptyset(&set);
	sigaddset(&set, SIGINT);	// C
	sigaddset(&set, SIGQUIT);	// <backsl>

	// ctrl C
	sa_newline.sa_handler = &handle_sa_newline;
	sa_newline.sa_flags = 0;
	sa_newline.sa_mask = set;
	sigaction(SIGINT, &sa_newline, NULL);

	// ctrl <backsl> --- nothing
	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	// sa_ignore.sa_mask = set;
	sigaction(SIGQUIT, &sa_ignore, NULL);
}

// void	setup_child_signals(void)
// {
// 	struct sigaction sa_default;

// 	sa_default.sa_handler = SIG_DFL;
// 	sa_default.sa_flags = 0;
// 	sigemptyset(&sa_default.sa_mask);

// 	sigaction(SIGINT, &sa_default, NULL);
// 	sigaction(SIGQUIT, &sa_default, NULL);
// }
