/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/06/22 23:16:39 by marvin            #+#    #+#             */
/*   Updated: 2024/06/22 23:16:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h" //modifica el nombre


// Rewrites the PWD and OLDPWD variables in the t_mshell struct
static void	change_pwd(t_mshell *minishell)
{
	char *temp;

	temp = ft_strdup(minishell->pwd);
	free(minishell->old_pwd);
	minishell->old_pwd = temp;
	free(minishell->pwd);
	minishell->pwd = getcwd(NULL, 0);
}

// Rewrites the PWD and OLDPWD variables in the envp array.
static void	change_envp(t_mshell *minishell)
{
	int i;
	char *temp;

	i = 0;
	while (minishell->envp[i])
	{
		if (ft_strncmp(minishell->envp[i], "PWD=", 4) == 0)
		{
			temp = ft_strjoin("PWD=", minishell->pwd);
			free(minishell->envp[i]);
			minishell->envp[i] = temp;
		}
		if (ft_strncmp(minishell->envp[i], "OLDPWD=", 7) == 0)
		{
			temp = ft_strjoin("OLDPWD=", minishell->old_pwd);
			free(minishell->envp[i]);
			minishell->envp[i] = temp;
		}
		i++;
	}
}

// Searchs in the env the variable HOME= or OLDPWD=
// if they dont exist anymore (e.g. because of 'unset'), error.
static int	change_directory(char **env, char *str)
{
	int		i;
	char	*new;

	i = -1;
	new = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
		{
			new = ft_strdup(env[i] + ft_strlen(str));
			break ;
		}
	}
	if (chdir(new) != 0)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" not set", 2);
		free(new);
		return (1);
	}
	if (!ft_strncmp("OLDPWD=", str, ft_strlen(str)))
		ft_putendl_fd(new, 1);
	free(new);
	return (0);
}

// cd ..
static void	ft_previous(t_mshell *minishell)
{
	int		last_slash;
	char	*pwd;
	char	*prev;
	int		i;

	pwd = minishell->pwd;
	i = 0;
	while (pwd[i])
	{
		if (pwd[i] == '/')
			last_slash = i;
		i++;
	}
	prev = ft_substr(pwd, 0, last_slash);
	chdir(prev);
	free(prev);
}

// CD only acepts one additional argument, if there are more, error.
// if no arguments, changes directoy to HOME.
// if '-' argument, changes directoy to the OLD PWD.
// if '..' argument, changes to previos directory.
// if '.' argument, nothing happens.
int	mini_cd(t_mshell *minishell, t_parser *commands)
{
	if (commands->str[1] && commands->str[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	else if (!commands->str[1])
		change_directory(minishell->envp, "HOME=");
	else if (!ft_strncmp(commands->str[1], "-", 1))
		change_directory(minishell->envp, "OLDPWD=");
	else if (!ft_strncmp(commands->str[1], "..", 2))
		ft_previous(minishell);
	else
	{
		if (ft_strncmp(commands->str[1], ".", 1)
			&& chdir(commands->str[1]) != 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(commands->str[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (EXIT_FAILURE);
		}
	}
	change_pwd(minishell);
	change_envp(minishell);
	return (0);
}

// minishell: cd: /Minishell: No such file or directory
