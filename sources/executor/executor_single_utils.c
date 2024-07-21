/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:50:18 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/21 02:55:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

// int	check_append_outfile(t_lexer *redirections)
// {
// 	int	flags;

// 	flags = O_CREAT | O_RDWR;
// 	if (redirections->token == GREAT_GREAT)
// 		flags = O_APPEND; //esta sobreescribiendo las anteriores
// 	else
// 		flags = O_TRUNC; //esta sobreescribiendo las anteriores
// 	return (open(redirections->str, flags, 0644));
// }

char	*make_single_str(char **array, t_mshell *data)
{
	char	*result;
	int		total_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	total_len = ft_arraylen(array);
	result = (char *)malloc(total_len + 1);
	if (!result)
		handle_error(data, 0);
	while (array[i])
	{
		ft_strcpy(result + j, array[i]);
		j += ft_strlen(array[i]);
		if (array[i + 1])
			result[j++] = ' ';
		i++;
	}
	result[j] = '\0';
	return (result);
}


char	**normalize_str_array(char **array, t_mshell *data)
{
	char	*joined_str;
	char	**updated_array;

	joined_str = make_single_str(array, data);
	ft_free_array(array);
	updated_array = ft_split(joined_str, ' ');
	free(joined_str);
	return (updated_array);
}

//se revisa que exista el ejecutable del comando standar (ejemplo ls, cat)
//estos comandos son parte de las utilidades del sistema y se proporciona con el sistema operativo
//en el while loop se busca la ubicacion del ejecutable del comando.
int	find_command(t_parser *cmd, t_mshell *data)
{
	int		i;
	char	*updated_command;
	char	**normalize_str;

	i = 0;
	normalize_str = normalize_str_array(cmd->str, data); //para que sirve esto? por ejemplo si tengo cat << LIM. 
	if (!access(normalize_str[0], F_OK))
		execve(normalize_str[0], normalize_str, data->envp); //normalize_str[0] es cat por ejemplo. pero no entiendo como funciona con el heredoc.
	while (data->paths[i])
	{
		updated_command = ft_strjoin(data->paths[i], normalize_str[0]);
		if (!access(updated_command, F_OK))
			execve(updated_command, normalize_str, data->envp);
		free(updated_command);
		i++;
	}
	return (handle_error3(data, 1, cmd->str[0])); //esta bien que resetee?	
	//ft_putstr_fd("Minishell: command not found: ", STDERR_FILENO); //falta lo de reset??
	//ft_putendl_fd(cmd->str[0], STDERR_FILENO);
	ft_free_array(normalize_str); //es necesario? no deberia directamnete resetar todo y por ende esto estaria ahi incluido???
	return (127); //???
}




// void	wait_for_child(t_mshell *data, int pid)
// {
// 	int	status;

// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 		data->exit_code = WEXITSTATUS(status);
// }
