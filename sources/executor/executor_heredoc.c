/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:27:45 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/21 01:48:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"


//crea el contenido de heredoc_content pero no hace nada si dentro hay funciones
int ft_heredoc (t_parser *commands, t_mshell *minishell)
{
	char *input_line;
	char *delimiter;
	int file;
	char *expanded_line;
	
	delimiter = commands->str;
	file = open(commands->hd_file_name, O_RDWR | O_CREAT | O_APPEND, 0644); //abro el hd file para escribirle data
	if(file < 0)
		return(handle_error(minishell, 8));
	if (dup2(file, STDOUT_FILENO) < 0)
	{	
		close(file);
		return (handle_error(minishell, 8));
	}
	
	while(1) //a;adir expander aca (ver si esta bien el que a;adi) // ver manejo de quotes, supuestamente habria que eliminarlas
	{
		input_line = readline("> ");
		if (!input_line) 
			return(EXIT_FAILURE); //CAMBIAR, NO HABRIA QUE AGREGARLO EN EL LEXER TAMBIEN?
		if (!ft_strncmp(input_line, delimiter, ft_strlen(delimiter)) && input_line[ft_strlen(delimiter)] == '\0') //si encuentra el limitador se termina
		{
			free(input_line);
			break;
		}
		else 
		{	
			expanded_line = expand_str(minishell, input_line); //revisar
			ft_putendl_fd(expanded_line, 1); //o deberia ser putstr? ver bien O_APPEND
			free(input_line); //o expanded_line?
		}	
	}
	close(file);
	return(EXIT_SUCCESS);	
}

char	*generate_name(void)
{
	static int	i;
	char		*file_num;
	char		*file_name;

	i = 0;
	file_num = ft_itoa(i++);
	file_name = ft_strjoin("/tmp/heredoc_", file_num);
	free(file_num);
	return (file_name);
}
