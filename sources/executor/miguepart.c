/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miguepart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:49:13 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/17 19:18:33 by miguandr         ###   ########.fr       */
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

int	handle_outfile(t_lexer *redirections)
{
	int	fd;

	fd = check_append_outfile(redirections);
	if (fd < 0)
	{
		ft_putstr_fd("minishell/outfile: Error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		close(fd);
		return (EXIT_FAILURE);
	}
	close (fd);
	return (EXIT_SUCCESS);
}

int	handle_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell/infile: No such file or directory\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("Minishell: pipe error\n", STDERR_FILENO);
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	check_redirections(t_parser *cmd)
{
	t_lexer	*start;

	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == LESS
			&& handle_infile(cmd->redirections->str) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if ((cmd->redirections->token == GREAT
				|| cmd->redirections->token == GREAT_GREAT)
			&& handle_outfile(cmd->redirections) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (cmd->redirections->token == HERE_DOC
			&& handle_infile(cmd->hd_file_name) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
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

int	find_command(t_parser *cmd, t_mshell *data) // resplit_str?
{
	int		i;
	char	*updated_command;
	char	**normalize_str;

	i = 0;
	normalize_str = normalize_str_array(cmd->str);
	if (!access(normalize_str[0], F_OK))
		execve(normalize_str[0], normalize_str, data->envp);
	while (data->paths[i])
	{
		updated_command = ft_strjoin(data->paths[i], normalize_str[0]);
		if (!access(updated_command, F_OK))
			execve(updated_command, normalize_str, data->envp);
		free(updated_command);
		i++;
	}
	ft_putstr_fd("Minishell: command not found: ", STDERR_FILENO);
	ft_putendl_fd(cmd->str[0], STDERR_FILENO);
	ft_free_array(normalize_str);
	return (127);
}

void	execute_command(t_parser *cmd, t_mshell *data)
{
	int	exit_status;

	exit_status = 0;
	if (check_redirections(cmd) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (cmd->builtins)
	{
		exit_status = cmd->builtins(data, cmd);
		exit(exit_status);
	}
	else
	{
		exit_status = find_command(cmd, data);
		exit(exit_status);
	}
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

t_parser	*call_expander(t_mshell *data, t_parser *cmd)
{
	t_lexer	*start;

	expander(data, cmd->str);
	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token != HERE_DOC)
			cmd->redirections->str = expand_str(data, cmd->redirections->str);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (cmd);
}

void	execute_single_cmd(t_parser *cmd, t_mshell *data)
{
	t_parser	*expanded_cmds;
	pid_t		pid;

	expanded_cmds = call_expander(data, cmd);
	if (cmd->builtins && is_main_process_builtin(cmd->builtins))
	{
		data->exit_code = cmd->builtins(data, cmd);
		return ;
	}
	//send_heredoc(data, cmd);
	pid = fork();
	if (pid < 0)
		handle_error(data, 5);
	else if (pid == 0)
		execute_command(expanded_cmds, data);
	wait_for_child(data, pid);
}

/*char	*make_single_str(char **array)
{
	char	*result;
	char	*temp;
	int		i;

	result = ft_strdup(array[0]);
	i = 1;
	while (array[i])
	{
		temp = ft_strjoin(result, " ");
		free(result);
		result = ft_strjoin(temp, array[i]);
		free(temp);
		i++;
	}
	return (result);
}*/
