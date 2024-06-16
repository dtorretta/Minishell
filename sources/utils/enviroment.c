/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:10:18 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/14 22:16:57 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

static int	set_pwd(char *env_var, char **pwd, int prefix_len)
{
	if (*pwd)
		free(*pwd);
	*pwd = ft_strdup(env_var + prefix_len);
	return (*pwd != NULL);
}

int	get_pwd(t_mshell *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PWD=", 4) == 0)
			return (set_pwd(data->envp[i], &(data->pwd), 4));
		if (ft_strncmp(data->envp[i], "OLDPWD=", 7) == 0)
			return (set_pwd(data->envp[i], &(data->pwd), 7));
		i++;
	}
	return (0);
}

char	*get_path(char **envp)
{
	char	*path_var;

	path_var = ft_strstr(envp, "PATH=");
	if (!path_var)
		return (ft_strdup(""));
	return (ft_substr(path_var + 5, 0, ft_strlen(path_var + 5)));
}

int	handle_envp(t_mshell *data)
{
	char	*path;
	char	*temp;
	size_t	len;
	int		i;

	path = get_path(data->envp);
	if (!path)
		return (EXIT_FAILURE);
	data->paths = ft_split(path, ':');
	free(path);
	if (!data->paths)
		return (EXIT_FAILURE);
	while (data->paths[i])
	{
		len = ft_strlen(data->paths[i]);
		if (len > 0 && data->paths[i][len - 1] != '/')
		{
			temp = ft_strjoin(data->paths, '/');
			free(data->paths);
			data->paths = temp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
