/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 01:12:17 by marvin            #+#    #+#             */
/*   Updated: 2024/06/15 01:12:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h" //modifica el nombre

int	mini_pwd(t_mshell *minishell, t_parser *commands)
{
	int		i;
	char	*pwd;

	(void)commands;
	i = 0;
	while (minishell->envp[i])
	{
		if (!ft_strncmp(minishell->envp[i], "PWD=", 4))
		{
			pwd = ft_substr(minishell->envp[i], 4,
					ft_strlen(minishell->envp[i]) - 4);
			ft_putendl_fd(pwd, 1);
			free (pwd);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
