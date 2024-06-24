/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:10:23 by marvin            #+#    #+#             */
/*   Updated: 2024/06/14 20:10:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h" //modifica el nombre

//echo command prints in the standar output the string passed as argument
//followed by a new line (ft_putendl_fd)
//echo -n doesn't print a new line (ft_putstr_fd)
//bash accept multiples -n
int	mini_echo(t_mshell *minishell, t_parser *commands)
{
	//el array de string tiene en el primer elemento la palabra echo, y en el siguiente puede ser tanto "-n" como el string a imprimir
	int	i;

	(void) minishell;
	i = 1;
	if (commands->str)
	{
		if (!ft_strncmp (commands->str[i], "-n", 3)) //esta bien 3? incluye el caracter nulo?
		{
			while (commands->str[i] && !ft_strncmp (commands->str[i], "-n", 3))
				i++;
			ft_putstr_fd(commands->str[i], 1);
		}
		else
			ft_putendl_fd(commands->str[i], 1);
	}
	return (EXIT_SUCCESS);
}

//HACER QUE IMPRIMA TOO EL ARRAY
