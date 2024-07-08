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

#include "../../includes/header.h" //modifica el nombre

//cuenta la cantidad de argumentos WORD que quedan antes del PIPE
//no deberian quedar redirecciones
static int	count_args(t_lexer *head, t_mshell *minishell)
{
	int		i;
	t_lexer	*current;

	i = 0;
	current = head;
	if (!current)
		return (handle_error(minishell, 4)); //ese necesario poner el return aca?
	while (current && current->token != PIPE)
	{
		if (current -> token != WORD)
			return (handle_error(minishell, 4)); //ese necesario poner el return aca?
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
static t_parser	*add_redirection(t_parser *commands, t_mshell *minishell) // Hay que quitar una variable de esta funcion. Máximo son 5 -.-' (gracias norminette)
{
	t_lexer	*current;
	t_lexer	*next_node;
	t_lexer	*node;
	int		arguments;
	char	**arg_array;
	int		i;

	current = minishell->lexer_list;
	while (current && current->token != PIPE)
	{
		if (current->token != WORD)
		{
			node = lexer_new_node(strdup(current->next->str), current->token ); //(OK)crea un nodo para la nueva sub linked list con las redirecciones
			lexer_add_last(&commands->redirections, node); //(OK) add el nodo a la sublinked list de redirecciones   (2)
			next_node = current->next->next;
			ft_delnode(current->next, &minishell->lexer_list);
			ft_delnode(current, &minishell->lexer_list);
			current = next_node;
			commands->num_redirections++;
		}
		else
			current = current->next;
	}

	arguments = count_args(minishell->lexer_list, minishell); //al nodo general le a;ade los token WORD
	arg_array = calloc ((arguments + 1), sizeof(char*));
	if (!arg_array)
		return (handle_error(minishell, 0)); //ese necesario poner el return aca?

	current = minishell->lexer_list; //devolvemos el puntero al primer elemento;
	i = 0;
	while (i < arguments)
	{
		arg_array[i] = strdup(current->str);
		next_node = current->next;
		ft_delnode(current, &minishell->lexer_list);
		i++;
		current = next_node;
	}
	commands->str = arg_array;
	commands->builtins = builtins_handler(commands->str[0]); //asigna el nombre de la funcion y pointer del builtin
	return ;
}

void	parser(t_mshell *minishell)
{
	t_parser	*node;
	t_mshell	*current;

	current = minishell;
	minishell->commands = NULL;
	while (current->lexer_list)
	{
		node = parser_new_node(minishell);
		add_redirection (node, minishell); //aca es donde le asigno a node las variables que faltan: redirections/ handle_builtins/ str
		parser_add_last(&minishell->commands, node);

		if (current->lexer_list && current->lexer_list->token == PIPE)
			ft_delnode(current->lexer_list, &minishell->lexer_list);
		//current = minishell; //es necesario??? parece que no
	}

    /*************FREES**********************/
    //no hay que ponerlo ahora, es solo a fin de chequeo de leaks
    //free_parser_list(minishell->commands);
    // if(minishell->envp)
    //     free_string_array(minishell->envp);
    //free(minishell);


	//free_string_array MIGUE YA TIENE ESTA FUNCION EN LIBFT
	//cambiar luego por ft_free_array
}
