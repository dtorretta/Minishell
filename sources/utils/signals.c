/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:31:02 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/16 20:29:26 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

/*testear in linux*/
void	handle_ctrl_c(int sig)
{
	(void)sig;
	//rl_redisplay();
	rl_replace_line("", 0);
	rl_on_new_line();
	//rl_set_prompt("");
	rl_redisplay();
	//rl_set_prompt("minishell> ");
}

void	handle_ctrl_backslash(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	init_signals(void)
{
	struct sigaction	sigint_action;
	struct sigaction	sigquit_action;

	sigint_action.sa_handler = handle_ctrl_c;
	sigemptyset(&sigint_action.sa_mask);
	sigint_action.sa_flags = 0;
	if (sigaction(SIGINT, &sigint_action, NULL) < 0)
	{
		perror("sigaction(SIGINT) failed");
		exit(EXIT_FAILURE);
	}

	sigquit_action.sa_handler = handle_ctrl_backslash; //SIG_IGN?
	sigemptyset(&sigquit_action.sa_mask);
	sigquit_action.sa_flags = 0;
	if (sigaction(SIGQUIT, &sigquit_action, NULL) < 0)
	{
		perror("sigaction(SIGQUIT) failed");
		exit(EXIT_FAILURE);
	}

	//signal(SIGINT, handle_ctrl_c);
	//signal(SIGQUIT, SIG_IGN); //
	//signal(SIGQUIT, handle_ctrl_backslash); /*test in linux*/
}

/*
int main() {
    // Initialize readline
    rl_bind_key('\t', rl_complete);

    // Initialize signals
    init_signals();

    // Main loop or other program logic
    while (1) {
        char *input = readline("minishell> ");
        if (!input) {
            printf("Exiting...\n");
            break;
        }
        add_history(input);
        // Process input or handle commands
        printf("Entered: %s\n", input);
        free(input);
    }

    return 0;
}
*/
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
}
*/
