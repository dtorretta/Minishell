/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:41 by marvin            #+#    #+#             */
/*   Updated: 2024/06/07 16:53:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h" //modifica el nombre

//DEBERIMOS ARGEGAR UN CONTROL QUE NO PERMITA PONER COMADOS COMO LS?

//void * es un tipo de dato especial que se utiliza como un "tipo genérico" o "tipo de puntero genérico". Esto significa que puede apuntar a cualquier tipo de dato
// puede apuntar a cualquier cosa: números, caracteres, matrices, estructuras o incluso funciones
//Al utilizar void *, el array puede contener punteros a funciones de diferentes tipos de retorno.
//Cada elemento de la matriz commands_array es una combinación de una cadena (char*) y un puntero a una función.

//builtins_handler es una funcion que toma un argumento (char *str) y devuelve un puntero a una funcion que toma dos argumentos (t_mshell *minishell) & (t_parser *commands)
//es una función que, cuando se llama con un argumento char *str, devuelve un puntero a otra función. 
//La función devuelta toma dos argumentos (ambos punteros a estructuras) y devuelve un entero
int (*builtins_handler(char *str))(t_mshell *minishell, t_parser *commands)
{
    //el puntero minishel y commands no se usa ahora, si no que es necesario dentro de las funciones 
    // ver si puedo pasar como parametro direecto el string
    static void *builtins_array [7][2] = {
        {"echo", mini_echo}, //TODO function
        {"cd", mini_cd}, //TODO function
        {"pwd", mini_pwd}, //TODO function
        {"export", mini_export}, //TODO function
        {"unset", mini_unset}, //TODO function
        {"env", mini_env}, //TODO function
        {"exit", mini_exit}, //TODO function    
    };
    int i;
    
    i = 0;    
    while(i < 7)
    {
        if (str && !ft_strncmp(builtins_array[i][0], str, ft_strlen(builtins_array[i][0])))
        {
            if (ft_strlen(str) != ft_strlen(builtins_array[i][0])) //ejemplo si tengo echoo.
                //add error y ver si contiene un return
                return(NULL);
            return (builtins_array[i][1]);
		}
		else    
            i++;
    }
    return (NULL);
}

t_parser	*parser_new_node(t_mshell *minishell)
{
    t_parser *new_node;
    
    new_node = (t_parser *)malloc(sizeof(t_parser));
	if (!new_node)
		return (handle_error(minishell, 0)); //ese necesario poner el return aca? tal vez me genere error porque la funcion retorna un int y mi funcion aca no
    
	new_node->num_redirections = 0;
	new_node->redirections = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->hd_file_name = NULL;
    
    return(new_node);
}

void	parser_add_last(t_parser **head, t_parser *new)
{
	t_parser	*tmp;

	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	
	
}

void	ft_delnode(t_lexer *temp, t_lexer  **head)
{
	if (temp->prev == NULL && temp->next == NULL)
	{
	    free(temp->str);
	    free(temp);
	    return;
    }
    if (temp->prev && temp->next) //si hay uno antes y uno despues
	{
	    temp->prev->next = temp->next;
	    temp->next->prev = temp->prev;
    }
    if (temp->prev == NULL && temp->next) //es el primer nodo
    {
        *head = temp->next;
        temp->next->prev = NULL;
    }
    if (temp->prev && temp->next == NULL) //es el ultimo nodo
    {
        temp->prev->next = NULL;
    }   
	free(temp->str);
	free(temp);
}


/*************FREES**********************/

void free_lexer_list(t_lexer *list) 
{
    t_lexer *temp;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->str);
        free(temp);
    }
}

void free_string_array(char **array) 
{
    if (array == NULL) {
        return;
    }

    int i = 0;
    while (array[i] != NULL) {
        free(array[i]); // Liberar cada string en el array
        array[i] = NULL; // Opcional: establecer a NULL después de liberar
        ++i;
    }
    free(array); // Liberar el array de punteros
}

void free_parser_list(t_parser *list) {
    t_parser *temp;
    while (list) {
        temp = list;
        list = list->next;
        free_string_array(temp->str);
        free_lexer_list(temp->redirections);
        free(temp);
    }
}