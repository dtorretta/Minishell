#include "../../includes/header_mig.h"

char	*remove_single_quote(char *str)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (i < len)
	{
		if (str[i] != '\'')
			result[j++] = str[i];
		i++;
	}
	return (result);
}

char	*single_quote_helper(char *str)
{
	char	*result;

	result = remove_single_quote(str);
	return (result);
}

char	*expand_double_quote_helper(t_mshell *data, char *str)
{
	char	*result;

	result = expand_double_quote(data, str);
	return (result);
}

char	*expand_variable_helper(t_mshell *data, char *str)
{
	char	*expanded_str;
	int		expanded_i;

	expanded_i = 0;
	expanded_str = expand_variable(data, str, &expanded_i);
	if (expanded_str)
		return (expanded_str);
	return (str);
}












int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	// Initialize mshell structure
	t_mshell data;
	data.envp = envp;
	data.paths = ft_split("/bin:/usr/bin", ':'); // Example paths
	data.exit_code = 0;

	// Initialize a sample command
	t_parser cmd;
	char *cmd_str[] = {"echo", "Hello, World!", NULL};
	cmd.str = cmd_str;
	cmd.redirections = NULL;
	cmd.hd_file_name = NULL;
	cmd.builtins = NULL;

	// Execute the command
	execute_single_cmd(&cmd, &data);

	// Clean up
	ft_free_array(data.paths);

	return data.exit_code;
}
