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
int mini_exit (t_mshell *minishell, t_parser *commands)
{
    if (commands == NULL || minishell == NULL) 
        return EXIT_FAILURE;
       
    ft_putendl_fd ("exit", 1);
        
    free_parser_list(commands);
    free_lexer_list(minishell->lexer_list);
    free_string_array(minishell->paths);
    free_string_array(minishell->envp);
    free(minishell->pwd); //imposible que este vacio?
    free(minishell->old_pwd); //imposible que este vacio?
    if(minishell->pid)
        free(minishell->pid);
    if(minishell->args)
        free(minishell->args);
    free(minishell);        
    
    return (EXIT_SUCCESS);
}