/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:00:30 by marvin            #+#    #+#             */
/*   Updated: 2024/06/14 23:00:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h" //modifica el nombre

//el bash real hace distincion sobre si despues del exit viene un numero, una letra etc.
//pero las instrucciones al decir que tenemos que implementar exit sin ninguna opcion, no agregue ese manejo de errores,
//esta bien?

void	free_minishell(t_mshell *minishell)
{
	free_parser_list(minishell->commands);
	free_lexer_list(minishell->lexer_list);
	free_string_array(minishell->paths); //cambiar luego por ft_free_array
	free_string_array(minishell->envp); //cambiar luego por ft_free_array
	free(minishell->pwd); //imposible que este vacio?
	free(minishell->old_pwd); //imposible que este vacio?
	if (minishell->pid)
		free(minishell->pid);
	if (minishell->args)
		free(minishell->args);
	free(minishell);
}

static int	is_num(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '+' || num[i] == '-')
		i++;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		else
			i++;
	}
	return (1);
}

int	mini_exit(t_mshell *minishell, t_parser *commands)
{
	int	exit_code;

	if (commands == NULL || minishell == NULL)
		return (EXIT_FAILURE);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (commands->str[1] && commands->str[2]) //si hay varios argumentos --> error
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE); //no libera la memoria
	}
	else if (!commands->str[1]) //si solo esta exit
		exit_code = 0;
	else //si solo hay un argumento --> ok
	{
		if (!is_num(commands->str[1])) //si algun caracter NO es numero //solo tiene en cuenta un + o - --> error
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(commands->str[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			return (EXIT_FAILURE); //no libera la memoria
		}
		else //si solo son numeros
			exit_code = ft_atoi(commands->str[1]);
	}
	free_minishell (minishell);
	exit (exit_code); //???????????? para que esta el exit?

	return (EXIT_SUCCESS);
}


// int mini_exit (t_mshell *minishell, t_parser *commands)
// {
//     int i;
//     int j;

//     if (commands == NULL || minishell == NULL)
//         return EXIT_FAILURE;
//     ft_putendl_fd ("exit", STDOUT_FILENO);
//     i = 1; //0 es exit

//     if (commands->str[2]) //si exit tiene mas de 1 argumentos
//     {
//         if (!is_alpha(commands->str[i])) //si algun caracter es letra
//         {
//             ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
//             ft_putendl_fd("too many arguments", STDERR_FILENO);
//         }
//     }

//     if (commands->str[1] && !commands->str[2]) //si exit tiene solo 1 argumentos
//     {
//         if (!is_num(commands->str[i])) //si algun caracter NO es numero //solo tiene en cuenta un + o -
//         {
//             ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
//             ft_putstr_fd(commands->str[i], STDERR_FILENO);
//             ft_putendl_fd(": numeric argument required", STDERR_FILENO);
//         }

//         else //si solo son numeros //hace falta hacer la distincion entre 0 y 1?
//         {
//             j = 0;
//             if (commands->str[i][j] == '+' || commands->str[i][j] == '-') //check
// 		        j++;
//             if(commands->str[i][j] != '0') //si el primer numero no es 0
//                 ft_putendl_fd("exit", STDERR_FILENO);
//             else //si el primer numero es 0
//             {
//                 while(commands->str[i][j] && commands->str[i][j] == '0')
//                     j++;
//                 if(commands->str[i][j]) //si todavia queda algun numero ej:00001
//                     ft_putendl_fd("exit", STDERR_FILENO);
//                 else //solo habian 0s
//                     ft_putendl_fd("exit", STDOUT_FILENO);
//             }
//         }
//     }
