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
	int	i;

	(void) minishell;
	i = 1;
	if (commands->str)
	{
		if (!ft_strncmp (commands->str[i], "-n", 3)) //esta bien 3? incluye el caracter nulo?
		{
			while (commands->str[i] && !ft_strncmp (commands->str[i], "-n", 3))
				i++;
			while (commands->str[i]) //NEW  // revisar si en el caso de (echo "hello" "world") lo imprime con espacio o no
				ft_putstr_fd(commands->str[i++], 1);
		}
		else
		{
			while (commands->str[i]) //NEW	
				ft_putendl_fd(commands->str[i++], 1);
		}
	}
	return (EXIT_SUCCESS);
}

//HACER QUE IMPRIMA TOO EL ARRAY

/*
- echo "hello" "world"
hello world

- echo "hello""world"
helloworld

- echo -n -n-n hola
-n-n hola

- echo #hola
- NADA

- echo "#hola"
#hola

*/
