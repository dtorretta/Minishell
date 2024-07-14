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
