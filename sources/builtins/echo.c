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

char *delete_quotes (char *str) ///agregar a utils //ver si la tiene migue
{
	char	*result;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	result = ft_calloc((len + 1), sizeof(char *));
	while (i < len)
	{
		if (str[i] != '\'' && str[i] != '\"')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	mini_echo(t_mshell *minishell, t_parser *commands)
{
	int	i;
	char *temp;

	(void) minishell;
	i = 1;
	if (commands->str)
	{
		if (!ft_strncmp (commands->str[1], "-n", 3)) //esta bien 3? incluye el caracter nulo?
		{
			while (commands->str[1] && !ft_strncmp (commands->str[1], "-n", 3)) //puede haber mas de 1
				i++;//pasa al sigueinte elemento del array
			temp = delete_quotes (commands->str[i]); //eliminar ""
			ft_putstr_fd(temp, 1);
		}
		else
		{
			temp = delete_quotes (commands->str[i]); //eliminar ""
			ft_putendl_fd(temp, 1);
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
