/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:21:41 by marvin            #+#    #+#             */
/*   Updated: 2024/06/07 16:21:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h" //modifica el nombre

//cuenta la cantidad de argumentos WORD que quedan antes del PIPE
//no deberian quedar redirecciones
int count_args (t_lexer *head)
{
	int i;
	t_lexer *current;
	
	i = 0;
	current = head;	
	if (!current)
		return (-1); //add error
	while (current && current->token != PIPE)
	{
		if (current -> token != WORD)
		    return(-1); //add error
		i++;
		current = current->next;
	}
	return (i);
}

//busca los tokens hasta que no queden mas o haya un PIPE
//si el token es uno de redireccion:
//crea un nuevo nodo y lo a;ade a la nueva sub linked list con las redirecciones
//lo elimina de la lexer_list original
//cuenta la cantidad de argumentos restantes (que solo deberian ser WORD)
//con calloc creo un array para almacenar todos los str (token WORD) + \0
//los array llevan doble pointer
t_parser *add_redirection (t_parser *commands, t_mshell *minishell)
{
	t_lexer *current;
	t_lexer *next_node;
	t_lexer *node;
	int arguments;
	char **arg_array;
	int i;
		
	current = minishell->lexer_list;	
	while(current && current->token != PIPE)
	{
		if(current->token != WORD)
		{
			node = ft_lexernew(strdup(current->next->str), current->token ); //(OK)crea un nodo para la nueva sub linked list con las redirecciones
			ft_lexeradd_back(&commands->redirections, node); //(OK) add el nodo a la sublinked list de redirecciones   (2)
    		next_node = current->next->next;
			ft_delnode(current->next, &minishell->lexer_list);
			ft_delnode(current, &minishell->lexer_list);
			current = next_node;
			commands->num_redirections++;
		}
		else
			current = current->next;
	}
	
	arguments = count_args(minishell->lexer_list); //al nodo general le a;ade los token WORD
	arg_array = calloc ((arguments + 1), sizeof(char*));
	if (!arg_array) //ver
		return; 
	
	current = minishell->lexer_list; //devolvemos el puntero al primer elemento;
	i = 0;  
	while (i < arguments)
	{
		arg_array[i] = strdup(current->str);
		ft_delnode(current, &minishell->lexer_list);
		i++;
		current = current->next;
	}
	commands->str = arg_array;
	commands->command_handler = command_handler(arg_array[0]); //PROBAR
	return;
}

void parser (t_mshell *minishell)
{
    t_parser *node;          
    t_mshell *current = minishell;
    
    minishell->commands = NULL;    
    while(current->lexer_list)
	{
		node = ft_parsernew();
		add_redirection (node, minishell);		
		ft_parseradd_back(&minishell->commands, node); 
		
		// ELIMINAR PIPE
		if(current->lexer_list && current->lexer_list->token == PIPE)
			ft_delnode(current->lexer_list, &minishell->lexer_list);
			
		//current = minishell; //es necesario??? parece que no
    }
    
    /*************FREES**********************/
    //no hay que ponerlo ahora, es solo a fin de chequeo de leaks
    free_parser_list(minishell->commands);
    free(minishell);
}