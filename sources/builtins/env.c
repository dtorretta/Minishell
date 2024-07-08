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
	
	if(commands->str[1]) //si tengo algo mas que env
	{
		ft_putstr_fd("env: ‘", STDERR_FILENO);
		ft_putstr_fd(commands->str[1], STDERR_FILENO);
		ft_putendl_fd("’: No such file or directory", STDERR_FILENO); 
		//reset_data(data);
		return(EXIT_FAILURE);
	}

	i = 0;
	while (minishell->envp[i])
	{
		ft_putendl_fd(minishell->envp[i], 1);
		i++;
	}
	return (EXIT_SUCCESS);
}
