/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:42:00 by afavier           #+#    #+#             */
/*   Updated: 2024/06/25 05:42:29 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

static void	flags_sig(int signal);

static int	nothing(void)
{
	return (0);
}

void	signal_init(void)
{
	struct sigaction	sig_action;

	g_sig = 0;
	sigemptyset(&sig_action.sa_mask);
	sig_action.sa_flags = 0;
	sig_action.sa_handler = flags_sig;
	sigaction(SIGINT, &sig_action, NULL);
	sig_action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_action, NULL);
	rl_event_hook = nothing;
}

static void	flags_sig(int signal)
{
	g_sig = signal;
	rl_replace_line("", 0);
	rl_done = 1;
}

void	signal_child(void)
{
	struct sigaction	sig_action;

	sigemptyset(&sig_action.sa_mask);
	sig_action.sa_flags = 0;
	sig_action.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sig_action, NULL);
	sigaction(SIGQUIT, &sig_action, NULL);
}

void	signal_wait(void)
{
	struct sigaction	sig_action;

	sigemptyset(&sig_action.sa_mask);
	sig_action.sa_flags = SA_RESTART;
	sig_action.sa_handler = flags_sig;
	sigaction(SIGINT, &sig_action, NULL);
	sigaction(SIGQUIT, &sig_action, NULL);
}
