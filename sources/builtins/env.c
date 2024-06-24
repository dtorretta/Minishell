/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:42:53 by marvin            #+#    #+#             */
/*   Updated: 2024/06/15 00:42:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h" //modifica el nombre

int	mini_env(t_mshell *minishell, t_parser *commands)
{
	int	i;

	(void)commands;
	i = 0;
	while (minishell->envp[i])
	{
		ft_putendl_fd(minishell->envp[i], 1);
		i++;
	}
	return (EXIT_SUCCESS);
}
