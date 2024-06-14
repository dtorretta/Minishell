#ifndef HEADER_H
# define HEADER_H //modifica el nombre

# include "../libft/includes/libft.h"
# include <stdarg.h> //?
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h> //?
# include <unistd.h>
# include <fcntl.h> //?
//# include <readline/readline.h>
//# include <readline/history.h>

/*******STRUCTURES*******/
typedef enum s_tokens
{
	WORD,
	PIPE,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

struct s_parser;
struct s_mshell;

//ESTA ES LA ESTRUCTURA FINAL QUE SE PASA AL EXECUTABLE
typedef struct s_mshell
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_parser         *commands;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*old_pwd;
	int						pipes; //ver si es necesario.
	int						*pid;
	//bool					heredoc;
	//bool					reset;
}	t_mshell; //t_tools;

typedef struct s_parser
{
	char					**str;
	int						(*builtins_handler)(t_mshell *, struct s_parser *); //Es un puntero a la funcion builtin que tiene 2 argumentos: Un puntero a t_mshell y Un puntero a t_parser
	int						num_redirections;
	char					*hd_file_name; //?
	t_lexer					*redirections;
	struct s_parser	   *next;
	struct s_parser	   *prev;
}	t_parser; //t_simple_cmds;


/*******LEXER*******/

/*-Token handling-*/
t_tokens	check_token(int c);
int			tokenizer(t_mshell *data);
int			handle_token(char *str, int i, t_lexer **lexer_list);
int			handle_word(char *str, int start, t_lexer **lexer_list);
/*-Quote handling-*/
int			count_quotes(char *str);
int			skip_quotes(const char *str, int start, char quote);
/*-Utils-*/
int			skip_space(char *str, int i);
int			add_node(char *str, t_tokens token, t_lexer **lexer_list);
t_lexer		*list_last(t_lexer *list);
void		lexer_error_check(t_lexer *lexer_list, t_mshell *data);
t_lexer		*lexer_new_node(char *str, int token);
void		lexer_add_last(t_lexer **list, t_lexer *new_node);

/*******ERROR HANDLING*******/
int			handle_error(t_mshell *data, int error);

/*******PARSER*******/
void parser (t_mshell *minishell);

/*******PARSER UTILS*******/
void	ft_delnode(t_lexer *temp, t_lexer  **lexer_list);
int (*command_handler (char *str))(t_mshell *minishell, t_parser *commands);
void	parser_add_last(t_parser **head, t_parser *new);
t_parser	*parser_new_node(t_mshell *minishell);

void free_lexer_list(t_lexer *list);
void free_string_array(char **array);
void free_parser_list(t_parser *list);

/*******builtins*******/
int mini_echo (t_mshell *minishell, t_parser *commands);
int mini_exit (t_mshell *minishell, t_parser *commands);

#endif // HEADER_H