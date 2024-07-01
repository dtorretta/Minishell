#include <unistd.h>
# include <stdio.h>
#include "../../includes/header.h" //modifica el nombre


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}


size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

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


void	ft_putstr_fd(const char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = strlen(src);
	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < (size -1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	size;

	if (!s)
		return (NULL);
	size = strlen(s);
	if (start > size)
		return (strdup(""));
	else if (len > size - start)
		len = size - start;
	substring = calloc(len + 1, sizeof(char));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, s + start, len + 1);
	return (substring);
}

// int	skip_space(char *str, int i)
// {
// 	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
// 		i++;
// 	return (i);
// }

// void print_array(char **array, int i)
// {
//     while (array[i])
//     {
//         ft_putstr_fd(array[i], STDERR_FILENO);
//         i++;
//         if(array[i])
//             write(2, " ", 1);        
//     }
    
// }

char *delete_quotes (char *str) //lo necesito en mas funciones?
{
    int i = 0;
    int last;
	char *temp;
	
	last = ft_strlen(str);
	if(str[i] == 34 || str[i] == 39)
	{
		while (str[i] == 34 || str[i] == 39)
			i++;
		temp = ft_substr(str, i, last - i - i);
	}
	else
		temp = str;
	return(temp);
}

int	echo(char **array)
{
	int	i;
	char *temp;

	i = 1;
	if (array)
	{
		if (!strncmp (array[1], "-n", 3)) //esta bien 3? incluye el caracter nulo?
		{
			while (array[1] && !strncmp (array[1], "-n", 3)) //puede haber mas de 1
				i++;//pasa al sigueinte elemento del array
			temp = delete_quotes (array[i]); //eliminar ""
			ft_putstr_fd(temp, 1);
		}
		else
		{
			temp = delete_quotes (array[i]); //eliminar ""
			ft_putendl_fd(temp, 1);
		}
	}
	return (EXIT_SUCCESS);
}

void print_array(char **array, int i) //BORRAR, ESTA EN UTILS
{
	while (array[i])
	{
		ft_putstr_fd(array[i], STDERR_FILENO);
		i++;
		if(array[i])
			write(2, " ", 1);        
	}
	
}

void print_string_array(char **array)
{
    int i = 0;

    // Recorrer el array hasta encontrar un NULL
    printf("\nARRAY\n");
    while (array[i] != NULL)
    {
        printf("String %d: %s\n", i + 1, array[i]);
        i++;
    }
}

char **new_array(char **array, char *str) //BORRAR, ESTA EN UTILS
{
	char **new_array;
	int i;
	
	i = 0;
	while(array[i])
		i++;
	new_array = calloc((i + 2), sizeof(char*));
	if (!new_array)
		return (NULL);
	i = 0;
	
	while(array[i])
	{
		new_array[i] = strdup(array[i]);
		i++;
	}
	new_array[i] = str;
	return(new_array);
}


char	*remove_single_quote(char *str)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	result = calloc((len + 1), sizeof(char *));
	while (i < len)
	{
		if (str[i] != '\'' && str[i] != '\"')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}



void coincidence (char **env, int i, char *add_var) //BORRAR, ESTA EN UTILS
{
	free(env[i]);
	env[i] = add_var;

}

static bool check_valid_identifier(char c) 
{
	// Verifica si el carácter c es válido como parte de un identificador de variable en Bash
	if ((c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9') ||
		c == '_' )
		return true;
	else 
		return false;
}

static char *check_quotes(char *str, char **var_name)
{
	//char **array;
	int i;
	char *temp;
	char *def;
	
	i = 0;
	while (str[i])
	{
		if(str[i] == '=')
		{
			i++;
			temp = ft_substr(str, 0, i); //export varname & =
			*var_name = strdup(temp); //revisar si esto sobrepasa esta funcion
			//i++;
			def = remove_single_quote(str + i); //contiene el string con la definicion
			temp = ft_strjoin(temp, def); //varname & = & def
			return(temp);
		}
		else
			i++;
	}
	*var_name = str;
	return(str);
}

static int error_check (char **array)
{
	int i;
	
	i = 0;
	if (array[2]) //si tengo mas de 3
	{
	    printf("error, mas de tres elementos\n");
	    print_string_array(array);

	    return(EXIT_FAILURE);		
    }
	else if (array[1])
	{
		if (ft_isdigit(array[1][0]) || array[1][0] == '=')
		{
	        printf("error, hay num\n");
            return(EXIT_FAILURE);	
		}
		while (array[1][i] != '=' && array[1][i]) 
		{
			if (!check_valid_identifier(array[1][i])) 
			{
	            printf("error, hay !\n");
	            return(EXIT_FAILURE);	
			}
			i++;
		}
	}
	return(EXIT_SUCCESS);
}

int export (char **array, char **env)
{
	int i;
	char **temp;
	char *add_var;
	char *var_name;
	
	i = -1;
	if(error_check(array)) //success 0 . failure 1
		return(EXIT_FAILURE);
	if(!array[1] || array[1][0] == '\0') //deberia imprimir algo mas que el enviroment???????
		printf("imprime enviroment\n");
	else
	{
		add_var = check_quotes(array[1], &var_name);//revisa si el string tiene "" en la definicion, de ser asi los elimina
		//add_var = var_name(temp); //revisa si el 3er elemento definicion de la variable tiene "" y vuelve a unir todo en un solo string
		
		printf("var name: %s\n", var_name);
		printf("add name: %s\n", add_var);
		
		
		while(env[++i])
		{
			if(!strncmp(env[i], var_name, ft_strlen(var_name))) //buscar en el array envp si se encuentra la variable definida con export
			{
				coincidence(env, i, add_var);
				return(EXIT_SUCCESS);
			}
		}
		//free(temp); //si no lo encontro, entonces a;adirlo al final del array.  
		temp = new_array(env, add_var);
		free(env);
		env = temp;
		printf("\n\nenvp nuevo: \n");
		print_string_array(env);
	}
	return(EXIT_SUCCESS);
}

char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = strdup(arr[i]);
		i++;
	}
	
    return (rtn);
}


int main(int argc, char **argv, char **env) 
{
    (void)argc;
    (void)argv;
    char *str[3] = {"export", "ZZZ=\"\"\"abc\"d\"\"\"", NULL};
    //char *str[2] = {"export", NULL};
    char **envp;
    
    envp = ft_arrdup(env);
    
    printf("envp original: \n");
    print_string_array(envp);
    printf("\n\noriginal: %s\n", str[1]);
    // //char *array[4] = {"char", "=", "hello", NULL};
    // // int i = 0;
    
    // //char *str;
    
    // ft_putstr_fd("minishell: export: `", STDERR_FILENO);
    // ft_putstr_fd(str, STDERR_FILENO);
    // ft_putendl_fd("': not a valid identifier", STDERR_FILENO);

    // int last;
    // int i = 0;
	// last = ft_strlen(str[1]);
	// char *temp;
	
	//printf("\nenvp nuevo: \n");
	
	
	export(str, envp);
	
	
	//printf("\nenvp nuevo: \n");
	//print_string_array(envp); //tengo problemas cuando imprimo el env aca
	
	
	
	// if(str[1][i] == 34 || str[1][i] == 39)
	// {
	// 	i++;
	// 	temp = ft_substr(str[1], i, last - i - 1);
	// }
	//printf("temp: %s\n", temp);
	
	
    //printf("%s\n", str);



    // while (str[i])
    // {
        
    //     if(str[i] == ' ')
    //     {
    //        i = skip_space(str, i);
    //        ft_putstr_fd("minishell: export: ", STDERR_FILENO);
    //        ft_putstr_fd(str + i, STDERR_FILENO);
    //        ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
    //        //error message
    //        return(EXIT_FAILURE); 
    //     }
    //     else
    //         i++;    
    // }
    // ft_putendl_fd(str + 2 , 1);
    
    // if (array[2])                
    // {
    //     ft_putstr_fd("minishell: export: ", STDERR_FILENO);
    //     print_array(array, 2); //que imprima del dos en adelante        
    //     ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
    //     return(EXIT_FAILURE);
    // }
    
    // int i = 3;
    // int start = 0;
    
    // start = ++i;
    
    // printf("%d\n", start);
    

    
    return (0);
    
    

}


 

// int **check_command(char *str, t_mshell *minishell)
// {
//     char **array;
//     int i;
//     char *temp;
    
//     i = 0;
//     while (str[i])
//     {
//         if(str[i] == '=')
//         {
//             array = calloc ((4), sizeof(char*));
//             temp = ft_substr(str, 0, i); //esta bien el len?
//             array[0] = temp;
//             array[1] = ft_strdup("=");
//             i++;
//             array[2] = ft_strdup(str + i);
//             return(array);            
//         }
//         else
//             i++;
//     }
//     array = calloc ((2), sizeof(char*));
// 	if (!array)
// 	    return (handle_error(minishell, 0)); //ese necesario poner el return aca?
//     array[0] = str; 
//     return(array); //MALLOCCCCC!!!!!//MALLOCCCCC!!!!!//MALLOCCCCC!!!!!//MALLOCCCCC!!!!!//MALLOCCCCC!!!!!
// }