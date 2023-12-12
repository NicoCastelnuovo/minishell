/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:35:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/10 17:45:02 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ctrl_c_pressed = 0;

/*
	SIGINT prints a new line.
	@line	rl_on_new_line() - tell the program to move to a new line
	@line	rl_redisplay() - update what is displayed, to reflect the buffer
*/
static void	handle_ctrl_c_before_rl(int sig_n)
{
	(void) sig_n;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_ctrl_c_pressed = 1;
}

void	handle_ctrl_c_after_rl(int sig_n)
{
	(void) sig_n;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	g_ctrl_c_pressed = 1;
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
	sa_newline.sa_handler = &handle_ctrl_c_before_rl;
	sa_newline.sa_flags = 0;
	sa_newline.sa_mask = set;
	sigaction(SIGINT, &sa_newline, NULL);

	// ctrl <backsl> --- nothing
	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	// sa_ignore.sa_mask = set;
	sigaction(SIGQUIT, &sa_ignore, NULL);

	struct termios config;

	tcgetattr(0, &config);
	config.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &config);
}

void	change_sig_handling(void)
{
	struct sigaction	sa_newline;
	sigset_t			set;

	ft_bzero(&sa_newline, sizeof(sa_newline));

	sigemptyset(&set);
	sigaddset(&set, SIGINT);	// C

	// ctrl C
	sa_newline.sa_handler = &handle_ctrl_c_after_rl;
	sa_newline.sa_flags = 0;
	sa_newline.sa_mask = set;
	sigaction(SIGINT, &sa_newline, NULL);
}
