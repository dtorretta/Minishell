#include "../../includes/header_mig.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(sizeof(char) * strlen(s1) + strlen(s2) + 1);
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		join[i++] = s1[j++];
	j = 0;
	while (s2[j])
		join[i++] = s2 [j++];
	join[i] = '\0';
	return (join);
}

int main (void)
{
	char *input_line;
	char *delimiter;
	char *heredoc_content = NULL;
	
	delimiter = "lim";
	while(1)
	{
		input_line = readline("> ");
		if (!input_line) 
            return(EXIT_FAILURE); //CAMBIAR, HNO HABRIA QUE AGREGARLO EN EL LEXER TAMBIEN?
		if (!strncmp(input_line, delimiter, strlen(delimiter)) && input_line[strlen(delimiter)] == '\0')
		{
		    if (!heredoc_content)
		        heredoc_content = "\n";
		    free(input_line); //es necesario??
		    break;
        }
        else 
		{
			if (!heredoc_content)
			{
			    heredoc_content = strdup(input_line);
                //heredoc_content = ft_strjoin (heredoc_content, '\n');
            }
			else 
			    heredoc_content = ft_strjoin(heredoc_content, input_line);
			//printf("VENIMOS BIEN\n");
			heredoc_content = ft_strjoin (heredoc_content, "\n");
        }
	}
	printf("%s", heredoc_content);
}