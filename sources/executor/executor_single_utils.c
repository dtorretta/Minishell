/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:50:18 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/17 19:51:04 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

int	check_append_outfile(t_lexer *redirections)
{
	int	flags;

	flags = O_CREAT | O_RDWR;
	if (redirections->token == GREAT_GREAT)
		flags = O_APPEND;
	else
		flags = O_TRUNC;
	return (open(redirections->str, flags, 0644));
}

char	*make_single_str(char **array)
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
		return (NULL);
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

char	**normalize_str_array(char **array)
{
	char	*joined_str;
	char	**updated_array;

	joined_str = make_single_str(array);
	ft_free_array(array);
	updated_array = ft_split(joined_str, ' ');
	free(joined_str);
	return (updated_array);
}

void	wait_for_child(t_mshell *data, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
}

int	is_main_process_builtin(int (*builtin)(t_mshell *, t_parser *))
{
	return (builtin == mini_cd || builtin == mini_exit
		|| builtin == mini_export || builtin == mini_unset);
}
