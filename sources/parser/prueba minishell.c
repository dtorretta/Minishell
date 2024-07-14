#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/header.h"


int	ft_iswhitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

void	ft_putstr_fd(const char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
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


void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

//esta funcion es parte del lexer.
//check con migue
t_lexer	*ft_lexernew(char *str, int token)
{
	t_lexer		*new_element;
	static int	i = 0;

	new_element = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->token = token;
	new_element->i = i++;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_lexeradd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	ft_parseradd_back(t_parser **lst, t_parser *new)
{
	t_parser	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	//new->next = NULL; //porque es necesario? si ya por default next es null?
}

// t_lexer *create_lexer_list() {
//     t_lexer *node_ls = (t_lexer *)malloc(sizeof(t_lexer));
//     if (!node_ls) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     node_ls->str = strdup("ls");
//     node_ls->token = WORD;
//     node_ls->i = 0;
//     node_ls->prev = NULL;
//     node_ls->next = NULL;

//     t_lexer *node_redirect = (t_lexer *)malloc(sizeof(t_lexer));
//     if (!node_redirect) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     node_redirect->str = strdup(">");
//     node_redirect->token = GREAT;
//     node_redirect->i = 1;
//     node_redirect->prev = node_ls;
//     node_redirect->next = NULL;

//     t_lexer *node_filename = (t_lexer *)malloc(sizeof(t_lexer));
//     if (!node_filename) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     node_filename->str = strdup("salida.txt");
//     node_filename->token = WORD;
//     node_filename->i = 2;
//     node_filename->prev = node_redirect;
//     node_filename->next = NULL;

//     t_lexer *node_pipe = (t_lexer *)malloc(sizeof(t_lexer));
//     if (!node_pipe) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     node_pipe->str = strdup("|");
//     node_pipe->token = PIPE;
//     node_pipe->i = 3;
//     node_pipe->prev = node_filename;
//     node_pipe->next = NULL;

//     t_lexer *node_grep = (t_lexer *)malloc(sizeof(t_lexer));
//     if (!node_grep) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     node_grep->str = strdup("grep");
//     node_grep->token = WORD;
//     node_grep->i = 4;
//     node_grep->prev = node_pipe;
//     node_grep->next = NULL;

//     t_lexer *node_palabra = (t_lexer *)malloc(sizeof(t_lexer));
//     if (!node_palabra) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     node_palabra->str = strdup("palabra");
//     node_palabra->token = WORD;
//     node_palabra->i = 5;
//     node_palabra->prev = node_grep;
//     node_palabra->next = NULL;

//     t_lexer *node_input_redirect = (t_lexer *)malloc(sizeof(t_lexer));
//     if (!node_input_redirect) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     node_input_redirect->str = strdup("<");
//     node_input_redirect->token = LESS;
//     node_input_redirect->i = 6;
//     node_input_redirect->prev = node_palabra;
//     node_input_redirect->next = NULL;

//     t_lexer *node_input_file = (t_lexer *)malloc(sizeof(t_lexer));
//     if (!node_input_file) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     node_input_file->str = strdup("entrada.txt");
//     node_input_file->token = WORD;
//     node_input_file->i = 7;
//     node_input_file->prev = node_input_redirect;
//     node_input_file->next = NULL;

//     t_lexer *node_output_redirect = (t_lexer *)malloc(sizeof(t_lexer));
//     if (!node_output_redirect) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     node_output_redirect->str = strdup(">");
//     node_output_redirect->token = GREAT;
//     node_output_redirect->i = 8;
//     node_output_redirect->prev = node_input_file;
//     node_output_redirect->next = NULL;

//     t_lexer *node_output_file = (t_lexer *)malloc(sizeof(t_lexer));
//     if (!node_output_file) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     node_output_file->str = strdup("salida_grep.txt");
//     node_output_file->token = WORD;
//     node_output_file->i = 9;
//     node_output_file->prev = node_output_redirect;
//     node_output_file->next = NULL;

//     // Enlazar los nodos
//     node_ls->next = node_redirect;
//     node_redirect->next = node_filename;
//     node_filename->next = node_pipe;
//     node_pipe->next = node_grep;
//     node_grep->next = node_palabra;
//     node_palabra->next = node_input_redirect;
//     node_input_redirect->next = node_input_file;
//     node_input_file->next = node_output_redirect;
//     node_output_redirect->next = node_output_file;

//     return node_ls; // Devolvemos el primer nodo de la lista
// }

t_lexer *create_lexer_list() {
    t_lexer *node_echo = (t_lexer *)malloc(sizeof(t_lexer));
    if (!node_echo) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node_echo->str = strdup("echo");
    node_echo->token = WORD;
    node_echo->i = 0;
    node_echo->prev = NULL;
    node_echo->next = NULL;

    t_lexer *node_dash_n1 = (t_lexer *)malloc(sizeof(t_lexer));
    if (!node_dash_n1) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node_dash_n1->str = strdup("hello");
    node_dash_n1->token = WORD;
    node_dash_n1->i = 1;
    node_dash_n1->prev = node_echo;
    node_dash_n1->next = NULL;

    // t_lexer *node_hello = (t_lexer *)malloc(sizeof(t_lexer));
    // if (!node_hello) {
    //     perror("malloc");
    //     exit(EXIT_FAILURE);
    // }
    // node_hello->str = strdup("extra");
    // node_hello->token = WORD;
    // node_hello->i = 2;
    // node_hello->prev = node_dash_n1;
    // node_hello->next = NULL;

    // t_lexer *node_world = (t_lexer *)malloc(sizeof(t_lexer));
    // if (!node_world) {
    //     perror("malloc");
    //     exit(EXIT_FAILURE);
    // }
    // node_world->str = strdup(" world");
    // node_world->token = WORD;
    // node_world->i = 3;
    // node_world->prev = node_hello;
    // node_world->next = NULL;

    //Enlazar los nodos
    node_echo->next = node_dash_n1;
    //node_dash_n1->next = node_hello;
    // node_hello->next = node_world;

    return node_echo; // Devolvemos el primer nodo de la lista
}

void print_lexer_list(t_lexer *head) {
    t_lexer *current = head;
    if(!current){
        printf("NULL EN LA LEXER LIST\n");
        return;
    }
    while (current != NULL) {

        printf("Str: %s, Token: %d, Index: %d\n", current->str, current->token, current->i);
        current = current->next;
    }
}

void print_parser_node(t_parser *node) {
    if (node == NULL) {
        return;
    }
    printf("\nParser Node:\n");
    if (node->str != NULL) {
        for (int i = 0; node->str[i] != NULL; i++) {
            printf("  str[%d]: %s\n", i, node->str[i]);
        }
    }
    if(!node->prev)
        printf("  PREV NULL\n");
    else
        printf("  PREV not NULL ⚠️\n");
    if(!node->next)
        printf("  NEXT NULL:\n");
    else
        printf("  NEXT not NULL ⚠️\n");
    printf("  num_redirections: %d\n", node->num_redirections);
    printf("  hd_file_name: %s\n", node->hd_file_name);
    printf("  Redirections:\n");
    print_lexer_list(node->redirections);
}

// Función para imprimir la lista enlazada t_parser
void print_parser_list(t_parser *head) {
    t_parser *current = head;
    while (current != NULL) {
        print_parser_node(current);
        current = current->next;
    }
}


void free_lexer_list(t_lexer *list) {
    t_lexer *temp;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->str);
        free(temp);
    }
}

void free_string_array(char **array) {
    if (array == NULL) {
        return; // No hacer nada si el array es NULL
    }

    for (int i = 0; array[i]; ++i) {
        free(array[i]); // Liberar cada string en el array
        array[i] = NULL; // Opcional: establecer a NULL después de liberar
    }
    printf("memory free");
    free(array); // Liberar el array de punteros
}

void free_parser_list(t_parser *list) {
    t_parser *temp;
    while (list) {
        temp = list;
        list = list->next;
        free_string_array(temp->str);
        free_lexer_list(temp->redirections);
        free(temp);
        //free(list);
    }
}

void	ft_delnode(t_lexer *temp, t_lexer  **lexer_list)
{
	
	if (temp == NULL) { //argregar
        return;
    }
	
	if (temp->prev == NULL && temp->next == NULL) //si es el unico elemento
	{
	    free(temp->str);
	    free(temp); //tambien tengo que borrar la memoria de los string???
	    *lexer_list = NULL; //agregar
	    //printf("\nultimo elemento FINAL\n");
	    return;
    }
    if (temp->prev && temp->next) //si hay uno antes y uno despues
	{
	    temp->prev->next = temp->next;
	    temp->next->prev = temp->prev;
    }
    if (temp->prev == NULL && temp->next) //es el primer nodo
    {
        *lexer_list = temp->next;
        temp->next->prev = NULL;
    }
    if (temp->prev && temp->next == NULL) //es el ultimo nodo
    {
        temp->prev->next = NULL;
    }   
	free(temp->str);
	free(temp); //tambien tengo que borrar la memoria de los string???
}

int count_args (t_lexer *lexer_list)
{
	int i;
	t_lexer *current;
	
	i = 0;
	current = lexer_list;	
	if (!current)
	{
		return (-1);//add error
    }
	while (current && current->token != PIPE)
	{
		if (current -> token != WORD) //si no hay solo words
		    return(-1); //add error
		i++;
		current = current->next;
		
	}
	return (i);
}

void borrar (t_mshell *minishell, t_parser *commands)
{
	(void) minishell;
	(void) commands;
	
	printf("HOLAAAAAAAAAAAAA");
}

int (*command_handler(char *str))(t_mshell *minishell, t_parser *commands)
{
    
    //el puntero minishel y commands no se usa ahora, si no que es necesario dentro de las funciones 
    // ver si puedo pasar como parametro direecto el string
    static void *commands_array [8][2] = {
        {"echo", borrar}, //TODO function
        {"cd", borrar}, //TODO function
        {"pwd", borrar}, //TODO function
        {"export", borrar}, //TODO function
        {"unset", borrar}, //TODO function
        {"env", borrar}, //TODO function
        {"exit", borrar}, //TODO function    
        {"ls", borrar}, //BORRAR    
    };
    int i;
    
    i = 0;    
    while(i < 7)
    {
        if (str && !strncmp(commands_array[i][0], str, strlen(commands_array[i][0])))
        {
            if (strlen(str) != strlen(commands_array[i][0])) //ejemplo si tengo echoo.
                //add error y ver si contiene un return
                return(NULL); //retorna null en vez de un pointer
            return (commands_array[i][0]);
		}
		else    
            i++;
    }
    return (NULL);
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

void add_redirection (t_parser *commands, t_mshell *minishell)
{
	t_lexer *current;
	t_lexer *next_node;
	t_lexer *node;
	int arguments;
	char **arg_array;
	int i;
	
	arguments = count_args(minishell->lexer_list); //BORRAR
	printf("\nCANTIDAD DE ARGUMENTOS: %d\n", arguments); //BORRAR
	
	current = minishell->lexer_list;	
	while(current && current->token != PIPE)
	{
		if(current->token != WORD)
		{
			node = ft_lexernew(strdup(current->next->str), current->token ); //(OK)crea un nodo para la nueva sub linked list con las redirecciones
			ft_lexeradd_back(&commands->redirections, node); //(OK) add el nodo a la sublinked list de redirecciones   (2)
    		next_node = current->next->next;
			ft_delnode(current->next, &minishell->lexer_list);
			ft_delnode(current, &minishell->lexer_list);
			current = next_node;
			
			commands->num_redirections++;
		}
		else
			current = current->next;
	}
	
	arguments = count_args(minishell->lexer_list); //al nodo general le a;ade los token WORD
	printf("\nCANTIDAD DE ARGUMENTOS: %d\n", arguments); //BORRAR esta bien que de 1 que son los word que quedan despues de las eliminaciones
	
	
	arg_array = calloc ((arguments + 1), sizeof(char*));
	if (!arg_array) //ver
		return; //no puedo hacer retur exit failor (1/4)
	current = minishell->lexer_list; //devolvemos el puntero al primer elemento;
	i = 0;
	
	printf("\nLEXER LIST antes de array:\n"); //BORRAR 1 elemento ls
	print_lexer_list(minishell->lexer_list); //BORRAR
	
	printf("\nCOMMAND LIST con las redirections:\n"); //BORRAR 2 elementos > y salida.txt
	print_lexer_list(commands->redirections); //BORRAR
        
	while (i < arguments)
	{
		arg_array[i] = strdup(current->str);
		next_node = current->next;
		ft_delnode(current, &minishell->lexer_list);
		i++;
		current = next_node; //aca esta el problema
	}
	print_string_array (arg_array); //1 solo elemento ls
	printf("\nLEXER LIST despues de array:\n"); //BORRAR
    print_lexer_list(minishell->lexer_list); //BORRAR
    
    commands->str = arg_array;
	commands->builtins_handler = command_handler(arg_array[0]);
    return;
}

t_parser	*ft_parsernew()
{
    t_parser *new_node;
    
    new_node = (t_parser *)malloc(sizeof(t_parser));
	if (!new_node)
		return (0);
    
	new_node->num_redirections = 0;
	new_node->redirections = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->hd_file_name = NULL;
    
    return(new_node);
}

char *delete_quotes (char *str) //ver si la tiene migue
{
	char	*result;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = strlen(str);
	result = calloc((len + 1), sizeof(char *));
	while (i < len)
	{
		if (str[i] != '\'' && str[i] != '\"')
			result[j++] = str[i];
		i++;
	}
	return (result);
}

int	mini_echo(t_mshell *minishell, t_parser *commands)
{
	int	i;
	char *temp;

	(void) minishell;
	i = 1;
	if (commands->str)
	{
		if (!strncmp (commands->str[1], "-n", 3)) //esta bien 3? incluye el caracter nulo?
		{
			while (commands->str[1] && !strncmp (commands->str[1], "-n", 3)) //puede haber mas de 1
				i++;//pasa al sigueinte elemento del array
			temp = delete_quotes (commands->str[i]); //eliminar ""
			ft_putstr_fd(temp, 1);
		}
		else
		{
			temp = delete_quotes (commands->str[i]); //eliminar ""
			ft_putendl_fd(temp, 1);
		}
	}
	free (temp);
	return (EXIT_SUCCESS);
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

int	mini_env(t_mshell *minishell, t_parser *commands)
{
	int	i;

	(void)commands;
	i = 0;
	if(commands->str[1]) //si tengo algo mas que env
	{
		ft_putstr_fd("env: ‘", STDERR_FILENO);                   
		ft_putstr_fd(commands->str[1], STDERR_FILENO);
		ft_putendl_fd("’: No such file or directory", STDERR_FILENO);
		//reset_data(data);
		return(EXIT_FAILURE);
	}
	
	while (minishell->envp[i])
	{
		ft_putendl_fd(minishell->envp[i], 1);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	mini_pwd(t_mshell *minishell, t_parser *commands)
{
	int		i;
	char	*pwd;

	(void)commands;
	i = 0;
	while (minishell->envp[i])
	{
		if (!strncmp(minishell->envp[i], "PWD=", 4))
		{
			pwd = ft_substr(minishell->envp[i], 4,
					strlen(minishell->envp[i]) - 4);
			ft_putendl_fd(pwd, 1);
			free (pwd);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

// void free_minishell (t_mshell *minishell) //lo necesito para alguna otra funcion?
// {
// 	free_parser_list(minishell->commands);
// 	free_lexer_list(minishell->lexer_list);
// 	free_string_array(minishell->paths);
// 	free_string_array(minishell->envp);
// 	free(minishell->pwd); //imposible que este vacio?
// 	free(minishell->old_pwd); //imposible que este vacio?
// 	if(minishell->pid)
// 		free(minishell->pid);
// 	if(minishell->args)
// 		free(minishell->args);
// 	free(minishell); 
// }

// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	return (0);
// }

// static int	is_num(char *num)
// {
// 	int	i;

// 	i = 0;
// 	if (num[i] == '+' || num[i] == '-')
// 		i++;
// 	while (num[i])
// 	{
// 		if (!ft_isdigit(num[i]))
// 			return (0);
// 		else
// 			i++;
// 	}
// 	return (1);
// }

// int mini_exit(t_mshell *minishell, t_parser *commands)
// {
// 	int exit_code;
	
// 	if (commands == NULL || minishell == NULL) 
// 		return EXIT_FAILURE;  	
// 	ft_putendl_fd("exit", STDOUT_FILENO);
// 	if (!commands->str[1]) //si solo esta exit
// 		exit_code = 0; 
// 	else if (is_num(commands->str[1]) && commands->str[2]) //si hay varios argumentos --> error // solo funciomna si el segundo argumento es numerico
// 	{
// 		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
// 		return (EXIT_FAILURE); //no libera la memoria yha que la ejecucion del programa no deberia terminar, tiene que dar la posibilidad de ingresar otro argumento
// 	}
// 	else //si solo hay un argumento --> ok
// 	{
//         if (!is_num(commands->str[1])) //si algun caracter NO es numero //solo tiene en cuenta un + o - --> error
//         {
//             ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
//             ft_putstr_fd(commands->str[1], STDERR_FILENO);
//             ft_putendl_fd(": numeric argument required", STDERR_FILENO);
//             return (EXIT_FAILURE); //no libera la memoria
//         }
// 		else //si solo son numeros
// 			exit_code = atoi(commands->str[1]);
// 	}	
// 	free_minishell (minishell);
// 	exit (exit_code); //finaliza el programa con un código de salida específico para el sistema operativo. Puede ser utilizado para determinar cómo terminó el programa
	
// 	//return (EXIT_SUCCESS); //nunca se va a ejecutar
// }

void initshell(t_mshell *minishell, char **env)
{
	minishell->args = NULL;
	minishell->commands = NULL;
	minishell->paths = NULL;
	minishell->envp = ft_arrdup(env);
	minishell->pwd = NULL;
	minishell->old_pwd = NULL;
	minishell->pid = NULL;
	
}

// static void	change_pwd(t_mshell *minishell)
// {
// 	char *temp;
	
// 	temp = strdup(minishell->pwd);
// 	free(minishell->old_pwd);
// 	minishell->old_pwd = temp;
// 	free(minishell->pwd);
// 	minishell->pwd = getcwd(NULL, 0);
// }

//reescribe en el array envp PWD y OLDPWD.
// static void	change_envp(t_mshell *minishell)
// {
// 	int	i;
// 	char *temp;

// 	i = 0;
// 	while (minishell->envp[i])
// 	{
// 		if (strncmp(minishell->envp[i], "PWD=", 4) == 0)
// 		{	
// 			temp = ft_strjoin("PWD=", minishell->pwd);
// 			free(minishell->envp[i]);
// 			minishell->envp[i] = temp;
// 		}	
// 		if (strncmp(minishell->envp[i], "OLDPWD=", 7) == 0)
// 		{	
// 			temp = ft_strjoin("OLDPWD=", minishell->old_pwd);
// 			free(minishell->envp[i]);
// 			minishell->envp[i] = temp;
// 		}	
// 		i++;
// 	}
// }


// static int	change_directory(char **env, char *str)
// {
// 	int	i;
// 	char *new;
// 	char *temp;

// 	i = 0;
// 	temp = ft_strjoin(str, "=");
// 	while (env[i])
// 	{
// 		if (strncmp(env[i], temp, strlen(temp)) == 0)
// 			new = strdup (env[i] + strlen(temp));
// 		i++;
// 	}
// 	if(chdir(new) != 0)
// 	{
// 		ft_putstr_fd(str, 2);
// 		ft_putendl_fd(" not set", 2);
// 		free(temp);
// 		free(new);
// 		return (1);
// 	}
// 	free(temp);
// 	free(new);
// 	return (0);
// }

// int mini_cd (t_mshell *minishell, t_parser *commands)
// {  
// 	if(commands->str[1] && commands->str[2]) //si hay mas de 2 argumentos (si no agrego str[1] cuando solo tengo un argumento me da error de jump)
// 	{
// 		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
	
// 	else if (!commands->str[1]) //si no hay argumentos
// 		change_directory(minishell->envp, "HOME");
		
// 	else if (!strncmp(commands->str[1], "-", 1)) 
// 		change_directory(minishell->envp, "OLDPWD");
	
// 	else
// 	{
// 		if (chdir(commands->str[1]) != 0) //error en el cambio de directorio
// 		{
// 			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
// 			ft_putstr_fd(commands->str[1], STDERR_FILENO);
// 			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	change_pwd(minishell);
// 	change_envp (minishell);
// 	return(0);
// }


static int	set_pwd(char *env_var, char **pwd, int prefix_len)
{
	if (*pwd)
		free(*pwd);
	*pwd = strdup(env_var + prefix_len);
	return (*pwd != NULL);
}

int	get_pwd(t_mshell *data) //cambiar a void
{
	int	i;

	i = 0;
	data->pwd = NULL;
	data->old_pwd = NULL;
	while (data->envp[i])
	{
		if (strncmp(data->envp[i], "PWD=", 4) == 0)
			set_pwd(data->envp[i], &(data->pwd), 4);
		if (strncmp(data->envp[i], "OLDPWD=", 7) == 0)
			set_pwd(data->envp[i], &(data->old_pwd), 7);
		i++;
	}
	return (1);
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

int	handle_error2(t_mshell *data, int error, char *str, char **array)
{
	(void)data;
	printf("fucking numero de error: %d\n", error);
	if(error == 1 || error == 2 || error == 4)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		if(error == 1)
			print_array(array, 2); //que imprima del dos en adelante  
		else if(error == 2 || error == 4)
			ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	}
	else if (error == 3)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);                   
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": event not found", STDERR_FILENO); 
	}
	else if (error == 5)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	//reset_data(data);
	return(EXIT_FAILURE);
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
	new_array[i] = str; //agrega la nueva variable como ultimo elemento
	return(new_array);
}


static int check_coincidence (t_mshell *minishell, int i, char *var_name, char *add_var)
{
	
	if(!strncmp(minishell->envp[i], var_name, strlen(var_name))) 
	{
		free(minishell->envp[i]);
		minishell->envp[i] = add_var;
		return(0);
	}
	return(1);
}


// //si encuentra un = crea array
// //array[0] --> nombre de la variable
// //array[1] --> =
// //array[2]--> nueva definificion
// //array[3]--> null
// //si recorre todo el while loop y no encontro nada, crea un array de 2 elementos donde el primero es todo el str y el 2do es NULL.

static bool check_valid_identifier(char c) 
{
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
	int i;
	char *temp;
	char *substr;
	
	i = 0;
	temp = delete_quotes(str);
	while (str[i])
	{
		if(str[i] == '=')
		{
			i++;
			//temp = delete_quotes(ft_substr(str, 0, i)); //export varname & =
			substr = ft_substr(str, 0, i);
			*var_name = delete_quotes(substr); //export varname & =   ////si uno todo en la mism a linea funciona pero da memory leaks
			//temp = delete_quotes(str);
			//*var_name = ft_strdup(temp); //revisar si esto sobrepasa esta funcion
			//def = delete_quotes(str + i); //lo que viene despues del ==
			//temp = ft_strjoin(temp, def); //varname & = & def
			free(substr);
			return(temp);
		}
		else
			i++;
	}
	*var_name = delete_quotes(str); //si no hay = de todos modos hay que darle valor a var name
	//temp = delete_quotes(str);
	return(temp);
}

static int error_check (t_mshell *minishell, t_parser *commands)
{
	int i;
	
	i = 0;
	if (commands->str[1] && commands->str[2]) //si tengo mas de 3
		return(handle_error2(minishell, 1, NULL, commands->str));		
	else if (commands->str[1])
	{
		if (isdigit(commands->str[1][0]) || commands->str[1][0] == '=')
		{
		    printf("ACA HAY =========================\n");
			return(handle_error2(minishell, 2, commands->str[1], NULL));
        }
		while (commands->str[1][i] != '=' && commands->str[1][i]) 
		{
			if (!check_valid_identifier(commands->str[1][i])) 
			{
				if (commands->str[1][i] == '!')
					return(handle_error2(minishell, 3, commands->str[1] + i, NULL));
				else
					return(handle_error2(minishell, 4, commands->str[1], NULL));
			}
			i++;
		}
	}
	return(EXIT_SUCCESS);
}

//str[0] --> export
//str[1] --> nombre de la variable (puede incluir la definicion)
//str[2] --> error ya que significa que el comando original tenia espacios
int mini_export (t_mshell *minishell, t_parser *commands)
{
	int i;
	char **temp;
	char *add_var;
	char *var_name;
	
	i = -1;
	if(error_check(minishell, commands)) //success 0 . failure 1
		return(EXIT_FAILURE);
	if(!commands->str[1] || commands->str[1][0] == '\0') //deberia imprimir algo mas que el enviroment???????
		mini_env(minishell, commands);
	else
	{
		add_var = check_quotes(commands->str[1], &var_name);//elimina los quotes de la variable (lo que esta antes de =)
		while(minishell->envp[++i])
		{
			if(check_coincidence(minishell, i, var_name, add_var) == 0)
			{	
			    return(EXIT_SUCCESS);	
            }
		}
		temp = new_array(minishell->envp, add_var);
		free_string_array(minishell->envp);		
		minishell->envp = temp;
		free(var_name);
	}
	return(EXIT_SUCCESS);
}

static char *check_quote(char *str) //no borrar, es distinta a la otra
{
	int i;
	char *temp;
	char *substr;
	
	i = 0;
	while (str[i])
	{
		if(str[i] == '=')
		{
			substr = ft_substr(str, 0, i);
			temp = delete_quotes(substr);
			free(substr);
			return(temp);
		}
		i++;
	}
	temp = delete_quotes(str); //si no hay = de todos modos hay que darle valor a var name
	return(temp);
}

static char **newarray(char **array, char *str)
{
	char **new_array;
	int i;
	int j;
	
	i = 0;
	while(array[i])
		i++;
	new_array = calloc((i), sizeof(char*));
	if (!new_array)
		return (NULL); //cambiar
	i = 0;
	j = 0;
	while(array[i])
	{
		if(!strncmp(array[i], str, strlen(str)))
		{
			//free(array[i]);
			i++;
		}
		new_array[j++] = strdup(array[i++]);
	}
	return(new_array);
}

int mini_unset (t_mshell *minishell, t_parser *commands)
{
	int i;
	char *env_var;
	char *unset_var;
	char **temp;
	
	i = -1;
	if(commands->str[1] && minishell->envp)
	{
		unset_var = check_quote(commands->str[1]);
		while(minishell->envp[++i])
		{
			env_var = check_quote(minishell->envp[i]); //separa de env pwd=lalal en solo pwd //revisar nombre funcion
			if(!strncmp(env_var, unset_var, strlen(unset_var))) //buscar en el array envp si se encuentra la variable definida con export
			{
				temp = newarray(minishell->envp, env_var);
				free_string_array(minishell->envp);
				//free(minishell->envp);
				minishell->envp = temp;
				if(!strncmp("PWD", unset_var, strlen(unset_var)))
				{
				    free(minishell->pwd);
				    minishell->pwd = NULL;
                }
                if(!strncmp("OLDPWD", unset_var, strlen(unset_var)))
				{
				    free(minishell->old_pwd);
				    minishell->old_pwd = NULL;
                }
                free(unset_var);
                free(env_var);
				return(EXIT_SUCCESS);
			}
			free(env_var); //si no lo encuentra
		}
		free(unset_var); //si no lo encuentra
		return(EXIT_SUCCESS); //si no hay coincidencia no pasa nada
	}
    return(EXIT_SUCCESS); 
}

int main(int argc, char **argv, char **env) 
{
    (void)argc;
    (void)argv;
    t_mshell *minishell;
    t_parser *node;
    
    minishell = (t_mshell *)malloc(sizeof(t_mshell));
    if (!minishell) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
          
    
    minishell->lexer_list = create_lexer_list(); //hard codding
    initshell(minishell, env);
    
    
    get_pwd(minishell);

    
    
    t_mshell *current = minishell;
    
    
    
    // Imprimir la lista de lexer
    printf("*********lista original************\n");
    print_lexer_list(minishell->lexer_list);
    
    int limite = 0;
    
    while(current->lexer_list && limite < 5)
	{
		node = ft_parsernew(); //aca aloco memoria al nuevo nodo
		add_redirection (node, minishell);
		ft_parseradd_back(&minishell->commands, node); 
		
		if(current->lexer_list && current->lexer_list->token == PIPE)	
		{
			printf("\n*********PIPE************\n");
			ft_delnode(current->lexer_list, &minishell->lexer_list);
			//break;
		}	
		limite++;	
		//current = minishell; //es necesario??? parece que no
    }

    // Imprimir la lista de lexer después de la llamada a prueba
    printf("\nfinal original\n"); //BORRAR
    print_lexer_list(minishell->lexer_list);//BORRAR
    
    
    printf("\n************final antes del execute****************\n"); //BORRAR
    print_parser_list(minishell->commands);//BORRAR
    
    
    
    printf("\n************COMMANDS TESTERS****************\n"); //BORRAR
    // mini_echo(minishell, minishell->commands);
    // printf("\nCHECK\n");
    
    // printf("\n***ANTES TEST**\n"); //BORRAR
    // printf("PWD: %s\n", minishell->pwd);
    // printf("OLD PWD: %s\n", minishell->old_pwd);
    
    // printf("\n***IMRPIMIR ARRAY**\n"); //BORRAR
    // print_string_array(env);
    // printf("\n");
    
    printf("\n***POST TEST**\n"); //BORRAR
    //mini_export(minishell, minishell->commands);
    mini_echo(minishell, minishell->commands);
    //mini_env(minishell, minishell->commands);
    //mini_pwd(minishell, minishell->commands);
    //mini_cd(minishell, minishell->commands);
    //mini_exit(minishell, minishell->commands);
    //mini_unset(minishell, minishell->commands);
    
    
    printf("\n***IMRPIMIR ARRAY**\n"); //BORRAR
    print_string_array(minishell->envp);
    printf("\n");
    
    //printf("PWD: %s\n", minishell->pwd);
    //printf("OLD PWD: %s\n", minishell->old_pwd);
    
    // /*************FREES**********************/
    // //⚠️ no hay que ponerlo ahora, es solo a fin de chequeo de leaks. ponerlo al final de todo cuando este todo terminado
 
    
    free_parser_list(minishell->commands);
    /*  
        free_string_array(temp->str);
        free_lexer_list(temp->redirections);
        free(temp);
    */
	free_lexer_list(minishell->lexer_list);
	free_string_array(minishell->paths);
	if (minishell->envp) 
	    free_string_array(minishell->envp);
	/*
	    free(array[i]); // Liberar cada string en el array
        free(array); // Liberar el array de punteros
	*/
	if (minishell->pwd)
	    free(minishell->pwd);
	if (minishell->old_pwd) 
	    free(minishell->old_pwd);
	if(minishell->pid)
		free(minishell->pid);
	if(minishell->args)
		free(minishell->args);
	free(minishell); 
	

    return 0;
}
