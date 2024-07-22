/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:31:02 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/22 19:36:15 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

/*testear in linux*/
void	handle_ctrl_c(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_ctrl_backslash(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	init_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGQUIT, handle_ctrl_backslash); /*esta se usara cuando se inicie un proceso*/
}

/*
int main(void) {
    char *input;

    // Initialize signal handlers
    init_signals();

    // Simple shell loop
    while (1) {
        input = readline("mini$hell> ");
        if (input == NULL) {
            ft_putstr_fd("exit\n", STDOUT_FILENO);
            break;
        }
        if (*input) {
            add_history(input);
        }
        free(input);
    }

    // Clean up readline history
    clear_history();

    return 0;
}*/
