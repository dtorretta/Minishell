#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/header.h"

/*********VARIOS********/
void free_string_array(char **array) {
    if (array == NULL) {
        return; // No hacer nada si el array es NULL
    }

    for (int i = 0; array[i] != NULL; ++i) {
        free(array[i]); // Liberar cada string en el array
        array[i] = NULL; // Opcional: establecer a NULL después de liberar
    }

    free(array); // Liberar el array de punteros
}
/*********SIGNALS*******/
void	ft_putstr_fd(const char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		n = -n;
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * (-1);
		ft_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(0 + n / 10, fd);
		ft_putchar_fd('0' + n % 10, fd);
	}
	else
		ft_putchar_fd('0' + n, fd);
}



/*testear in linux*/
void	handle_ctrl_c(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_ctrl_backslash(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	init_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGQUIT, handle_ctrl_backslash); /*esta se usara cuando se inicie un proceso*/
}
/*******LIBFT***********/
int	ft_iswhitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needlen;

	if (*needle == 0)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	needlen = strlen(needle);
	while (*haystack && needlen <= len)
	{
		if (*haystack == *needle && strncmp(haystack, needle, needlen) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (((unsigned char)s1[i] == (unsigned char)s2[i]) && (s1[i] != '\0'
			|| s2[i] != '\0') && (i < n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

char	*ft_strchr(const char *str, int c)
{
	while (*str && *str != (unsigned char)c)
		str++;
	if (*str == (unsigned char)c)
		return ((char *)str);
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (strdup(s1));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = strlen(s1) - 1;
	while (end && ft_strchr(set, s1[end]))
		end--;
	trim = ft_substr(s1, start, end - start +1);
	return (trim);
}

static size_t	ft_words(char const *s, char delimiter)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		while (s[i] && s[i] == delimiter)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != delimiter)
				i++;
			size++;
		}
	}
	return (size);
}

static char	**ft_allocation(char **array, char const *s, char c)
{
	int		i;
	size_t	count;
	int		start;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			array[count] = ft_substr(s, start, (i - start));
			count++;
		}
	}
	array[count] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (ft_words(s, c) + 1));
	if (!array)
		return (NULL);
	ft_allocation(array, s, c);
	return (array);
}


int	handle_error(t_mshell *data, int error)
{
	(void)data;
	const char	*message;
	const char	*error_message[] = {
		"memory error: unable to allocate memory\n",
		"syntax error: unable to find closing quotation\n",
		"syntax error: command line can not begin/end with a token\n",
		"syntax error: too many consecutive tokens\n",
		"syntax error: wrong token handling\n",
	};

	message = error_message[error];
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(message, 1);
	//reset_data(data);
	return (EXIT_FAILURE);
}

/*******PARSER 2.0******/

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

/******ENVIROMENT*******/

static int	set_pwd(char *env_var, char **pwd, int prefix_len)
{
	int	i = 0;

	if (*pwd)
		free(*pwd);
	*pwd = strdup(&env_var[i + prefix_len]);
	return (*pwd != NULL);
}

int	get_pwd(t_mshell *data)
{
	int	i;

	i = 0;
	data->pwd = NULL;
	data->old_pwd = NULL;
	//printf("\nCHECK\n");
	while (data->envp[i])
	{

		if (ft_strncmp(data->envp[i], "PWD=", 4) == 0)
		{
			//printf("\nCHECK 2 i: %d\n", i);
			set_pwd(data->envp[i], &(data->pwd), 4);
			//printf("\nCHECK 3\n");
		}
		if (ft_strncmp(data->envp[i], "OLDPWD=", 7) == 0)
		{
			//printf("\nCHECK 4\n");
			set_pwd(data->envp[i], &(data->pwd), 7);
			//printf("\nCHECK 5\n");
		}
		i++;
	}

	return (1);
}

char	*get_path(char **envp)
{
	char	*path_var;

	path_var = ft_strnstr(*envp, "PATH=", 5);
	if (!path_var)
		return (strdup(""));
	return (ft_substr(path_var + 5, 0, strlen(path_var + 5)));
}

int	handle_envp(t_mshell *data)
{
	char	*path;
	char	*temp;
	size_t	len;
	int		i;

	i = 0;
	path = get_path(data->envp);
	if (!path)
		return (EXIT_FAILURE);
	data->paths = ft_split(path, ':');
	free(path);
	if (!data->paths)
		return (EXIT_FAILURE);
	while (data->paths[i])
	{
		len = strlen(data->paths[i]);
		if (len > 0 && data->paths[i][len - 1] != '/')
		{
			temp = ft_strjoin(*data->paths, (const char *)'/');
			free(data->paths[i]);
			data->paths[i] = temp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}


/********MAIN*******/

char	**dup_str(char **array)
{
	char	**result;
	size_t	i;

	i = 0;
	if (array == NULL)
		return (NULL);
	while (array[i] != NULL)
		i++;
	result = calloc(sizeof(char *), i + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (array[i])
	{
		result[i] = strdup(array[i]);
		if (result[i] == NULL)
		{
			free_string_array(result);
			return (NULL); // probar return (result) en caso de fallo!!
		}
		i++;
	}
	return (result);
}

int	init_data(t_mshell *data)
{
	data->commands = NULL;
	data->lexer_list = NULL;
	data->reset = false;
	data->pid = NULL;
	data->heredoc = false;
	//g_global.stop_heredoc = 0;
	//g_global.in_cmd = 0;
	//g_global.in_heredoc = 0;
	handle_envp(data);
	init_signals();
	return (1);
}


/*******LEXER*******/

int	skip_space(char *str, int i)
{
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	return (i);
}

t_lexer	*list_last(t_lexer *list)
{
	t_lexer	*temp;

	if (!list)
		return (NULL);
	temp = list;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

static int	check_edges(t_lexer *list)
{
	if (list->token != WORD || list_last(list)->token != WORD)
		return (0);
	return (1);
}

static int	check_invalid_sequence(t_lexer *list)
{
	while (list && list->next)
	{
		if (list->token != WORD && list->next->token != WORD)
			return (0);
		list = list->next;
	}
	return (1);
}

void	lexer_error_check(t_lexer *lexer_list, t_mshell *data)
{
	if (!lexer_list)
		EXIT_SUCCESS ;
	if (!check_edges(lexer_list))
		handle_error(data, 2);
	if (!check_invalid_sequence(lexer_list))
		handle_error(data, 3);
}

t_lexer	*lexer_new_node(char *str, int token)
{
	static int	index = 0;
	t_lexer		*new_node;

	new_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->str = str;
	new_node->token = token;
	new_node->i = index++;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	lexer_add_last(t_lexer **list, t_lexer *new_node)
{
	t_lexer	*last;

	last = NULL;
	if (!list || !new_node)
		return ;
	if (*list == NULL)
		*list = new_node;
	else
	{
		last = list_last(*list);
		last->next = new_node;
		new_node->prev = last;
	}
}

int	add_node(char *str, t_tokens token, t_lexer **lexer_list)
{
	t_lexer	*node;

	node = lexer_new_node(str, token);
	if (!node)
		return (0);
	if (*lexer_list == NULL)
		*lexer_list = node;
	else
		lexer_add_last(lexer_list, node);
	return (1);
}

static int	find_next_quote(char *str, int start, char target)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (str[i] == target && (i == 0 || str[i - 1] != '\\'))
			return (i);
		i++;
	}
	return (-1);
}

int	count_quotes(char *str)
{
	int		i;
	int		single_quote;
	int		double_quote;

	i = -1;
	single_quote = 0;
	double_quote = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = find_next_quote(str, i + 1, str[i]);
			if (i == -1)
				return (0);
			if (str[i] == '\'')
				single_quote += 2;
			else if (str[i] == '"')
				double_quote += 2;
		}
	}
if (single_quote == 0 || (single_quote > 0 && single_quote % 2 == 0)
		|| (double_quote == 0 || (double_quote > 0 && double_quote % 2 == 0)))
		return (1);
	return (0);
}

int	skip_quotes(const char *str, int start, char quote)
{
	int	len;

	len = 0;
	if (str[start] == quote)
	{
		len++;
		start++;
		while (str[start + len] && str[start + len] != quote)
			len++;
		if (str[start + len] == quote)
			len++;
	}
	return (len);
}


t_tokens	check_token(int c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (GREAT);
	else if (c == '<')
		return (LESS);
	else
		return (0);
}

static int	process_double(char *str, int i, t_tokens token, t_lexer **list)
{
	t_tokens	double_token;

	if (token == GREAT && check_token(str[i + 1]) == GREAT)
		double_token = GREAT_GREAT;
	else if (token == LESS && check_token(str[i + 1]) == LESS)
		double_token = HERE_DOC;
	else
		return (0);
	if (!add_node(NULL, double_token, list))
		return (-1);
	return (2);
}

static int	process_single(t_tokens token, t_lexer **list)
{
	if (!add_node(NULL, token, list))
		return (-1);
	return (1);
}

int	handle_token(char *str, int i, t_lexer **lexer_list)
{
	t_tokens	token;
	int			result;

	token = check_token(str[i]);
	if (token == GREAT || token == LESS)
	{
		result = process_double(str, i, token, lexer_list);
		if (result != 0)
			return (result);
	}
	if (token)
		return (process_single(token, lexer_list));
	return (0);
}

int	handle_word(char *str, int start, t_lexer **lexer_list)
{
	int	len;

	len = 0;
	while (str[start + len] && (!check_token(str[start + len])
			&& !ft_iswhitespace(str[start + len])))
	{
		len += skip_quotes(str, start + len, 34);
		len += skip_quotes(str, start + len, 39);
		if (str[start + len] && (!check_token(str[start + len])
				&& !ft_iswhitespace(str[start + len])))
			len++;
	}
	if (!add_node(ft_substr(str, start, len), WORD, lexer_list))
		return (-1);
	return (len);
}


int	tokenizer(t_mshell *data)
{
	int	i;
	int	handled;

	i = 0;
	while (data->args[i])
	{
		i = skip_space(data->args, i);
		handled = 0;
		if (check_token(data->args[i]))
			handled = handle_token(data->args, i, &data->lexer_list);
		else
			handled = handle_word(data->args, i, &data->lexer_list);
		if (handled < 0)
			return (0);
		i += handled;
	}
	return (1);
}

int	lexer(t_mshell *data)
{
	const char	*prompt;
	char		*user_input;
	char		*trimmed_input;

	prompt = "minishell> ";
	user_input = readline(prompt);
	trimmed_input = ft_strtrim(user_input, " ");
	free(user_input);
	data->args = trimmed_input;
	if (!data->args)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	//if (*data->args == '\0')
		//return (reset_data(data));
	add_history(data->args);
	if (!count_quotes(data->args))
		return (handle_error(data, 1));
	if (!tokenizer(data))
		return (handle_error(data, 0));
	lexer_error_check(data->lexer_list, data);
	return (1);
}


/*******PARSER*******/

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



void free_parser_list(t_parser *list) {
    t_parser *temp;
    while (list) {
        temp = list;
        list = list->next;
        free_string_array(temp->str);
        //free(temp->str); //creo que no alazanza solo asi
        free_lexer_list(temp->redirections);
        free(temp);
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
        printf("%s\n", array[i]);
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
			node = lexer_new_node(strdup(current->next->str), current->token ); //(OK)crea un nodo para la nueva sub linked list con las redirecciones
			lexer_add_last(&commands->redirections, node); //(OK) add el nodo a la sublinked list de redirecciones   (2)
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

int mini_echo (t_mshell *minishell, t_parser *commands)
{
    (void) minishell;

    //el array de string tiene en el primer elemento la palabra echo, y en el siguiente puede ser tanto "-n" como el string a imprimir
    int i;

    i = 1;
    if (commands->str)
    {
        if (!strncmp (commands->str[i], "-n", 3)) //esta bien 3? incluye el caracter nulo?
        {
            while (commands->str[i] && !strncmp (commands->str[i], "-n", 3))
                i++;
            ft_putstr_fd(commands->str[i], 1);
        }
        else
            ft_putendl_fd(commands->str[i], 1);
    }
    return (EXIT_SUCCESS);
}

int mini_exit (t_mshell *minishell, t_parser *commands)
{
    if (commands == NULL || minishell == NULL)
        return EXIT_FAILURE;

    ft_putendl_fd ("exit", 1);

    free_parser_list(commands);
    free_lexer_list(minishell->lexer_list);
    //free_string_array(minishell->paths);
    //free_string_array(minishell->envp);
    //free(minishell->pwd); //imposible que este vacio?
    //free(minishell->old_pwd); //imposible que este vacio?
    // if(minishell->pid)
    //     free(minishell->pid);
    // if(minishell->args)
    //     free(minishell->args);
    free(minishell);

	return(1); //CHANGE 2!
}

int mini_env (t_mshell *minishell, t_parser *commands)
{
    (void)commands;
    int i = 0;

    printf("check⚠️\n");
    // Recorrer el array hasta encontrar un NULL
    while (minishell->envp[i])
    {
        //printf("%s\n", minishell->envp[i]);
        ft_putendl_fd(minishell->envp[i], 1);
        i++;
    }
	return(1); //CHANGE 1!
}

int mini_pwd (t_mshell *minishell, t_parser *commands)
{
    (void)commands;
    int i = 0;
    char *pwd;

    while (minishell->envp[i])
    {
        if (!strncmp(minishell->envp[i], "PWD=", 4))
        {
            pwd = ft_substr(minishell->envp[i], 4, strlen(minishell->envp[i]) - 4);
            ft_putendl_fd(pwd, 1);
            free (pwd);
            return(EXIT_SUCCESS);
        }
        i++;
    }
    return(EXIT_FAILURE);
}

void initshell(t_mshell *minishell)
{
	minishell->commands = NULL; //parser
	minishell->pid = NULL; //lexer

}

void parser (t_mshell *minishell)
{
    t_parser *node;

    //minishell->lexer_list = create_lexer_list(); //hard codding
    initshell(minishell);
    t_mshell *current = minishell;

    // Imprimir la lista de lexer
    printf("*********lista original************\n");
    print_lexer_list(minishell->lexer_list);

    while(current->lexer_list)
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
		//current = minishell; //es necesario??? parece que no
    }

    // Imprimir la lista de lexer después de la llamada a prueba
    printf("\nfinal original\n"); //BORRAR
    print_lexer_list(minishell->lexer_list);//BORRAR


    printf("\n************final antes del execute****************\n"); //BORRAR
    print_parser_list(minishell->commands);//BORRAR


    //printf("\n************COMMANDS TESTERS****************\n"); //BORRAR
    //mini_pwd(minishell, minishell->commands);
    printf("\nCHECK\n");

    /*************FREES**********************/
    //⚠️ no hay que ponerlo ahora, es solo a fin de chequeo de leaks. ponerlo al final de todo cuando este todo terminado
	free_parser_list(minishell->commands);
	if (minishell->envp)
		free_string_array(minishell->envp);

	if (minishell->paths)
		free_string_array(minishell->paths);

	if (minishell->args)
		free(minishell->args);

	if (minishell->pwd)
		free(minishell->pwd);

	if (minishell->old_pwd)
		free(minishell->old_pwd);

	if (minishell->pid)
		free(minishell->pid);
    //free(minishell);


    return;



}

int	main(int ac, char **av, char **envp)
{
	t_mshell	data;

	if (ac != 1 || av[1])
	{
		printf("Minishell does not accept arguments\n");
		exit (0);
	}
	data.envp = dup_str(envp);

	//print_string_array(data.envp);

	get_pwd(&data);
	init_data(&data);
	printf("MAKE WELCOME MESSAGE/n"); //MAKE
	lexer(&data);
	parser(&data);
	//prepare_executor(&data); // ??
	//reset_data(&data);
	return (0);
}
/*

==102907== 4,272 bytes in 71 blocks are still reachable in loss record 53 of 67
==102907==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==102907==    by 0x496C58E: strdup (strdup.c:42)
==102907==    by 0x40239E: dup_str (in /home/miguandr/Documents/Projects/rank_3/Minishell/sources/parser/test)
==102907==    by 0x403EB3: main (in /home/miguandr/Documents/Projects/rank_3/Minishell/sources/parser/test)



==102907== 576 bytes in 1 blocks are still reachable in loss record 26 of 67
==102907==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==102907==    by 0x402356: dup_str (in /home/miguandr/Documents/Projects/rank_3/Minishell/sources/parser/test)
==102907==    by 0x403EB3: main (in /home/miguandr/Documents/Projects/rank_3/Minishell/sources/parser/test)


==102907== 66 bytes in 1 blocks are still reachable in loss record 18 of 67
==102907==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==102907==    by 0x496C58E: strdup (strdup.c:42)
==102907==    by 0x402107: set_pwd (in /home/miguandr/Documents/Projects/rank_3/Minishell/sources/parser/test)
==102907==    by 0x402050: get_pwd (in /home/miguandr/Documents/Projects/rank_3/Minishell/sources/parser/test)
==102907==    by 0x403EC0: main (in /home/miguandr/Documents/Projects/rank_3/Minishell/sources/parser/test)

==102907== 8 bytes in 1 blocks are still reachable in loss record 1 of 67
==102907==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==102907==    by 0x401C36: ft_split (in /home/miguandr/Documents/Projects/rank_3/Minishell/sources/parser/test)
==102907==    by 0x402208: handle_envp (in /home/miguandr/Documents/Projects/rank_3/Minishell/sources/parser/test)
==102907==    by 0x402448: init_data (in /home/miguandr/Documents/Projects/rank_3/Minishell/sources/parser/test)
==102907==    by 0x403EC9: main (in /home/miguandr/Documents/Projects/rank_3/Minishell/sources/parser/test)



==102907==    still reachable: 209,097 bytes in 296 blocks


*/
