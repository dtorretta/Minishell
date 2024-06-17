/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:31:22 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/17 16:13:52 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header_mig.h"

int	main(int ac, char **av, char **envp)
{
	t_mshell	data;

	if (ac != 1 || av[1])
	{
		printf("Minishell does not accept arguments\n");
		exit(0);
	}
	data.envp = dup_str(envp);
	get_pwd(&data);
	init_data(&data);
	// printf("MAKE WELCOME MESSAGE/n"); //MAKE
	lexer(&data);
	parser(&data);
	// prepare_executor(&data); // ??
	reset_data(&data);
	return (0);
}
