#ifndef HEADER_H
# define HEADER_H //modifica el nombre

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"


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

// typedef struct s_parser_tools
// {
// 	t_lexer			*lexer_list;
// 	t_lexer			*redirections;
// 	int				num_redirections;
// 	struct s_tools	*tools;
// }	t_parser_tools;

//ESTA ES LA ESTRUCTURA FINAL QUE SE PASA AL EXECUTABLE
typedef struct s_mshell
{
	char					*args;
	char					**paths;
	char					**envp;
	//t_parser	            *commands;
	struct s_parser *commands;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*old_pwd;
	int						pipes; //ver si es necesario. originalmente
	int						*pid;
	//bool					heredoc;
	//bool					reset;
}	t_mshell; //t_tools;

typedef struct s_parser
{
	char					**str;
	int						(*command_handler)(t_mshell *, struct s_parser *); //Es un puntero a la funcion builtin que tiene 2 argumentos: Un puntero a t_mshell y Un puntero a t_parser
	int						num_redirections;
	char					*hd_file_name; //?
	t_lexer					*redirections;
	struct s_parser	   *next;
	struct s_parser	   *prev;
}	t_parser; //t_simple_cmds;


/*PARSER UTILS*/
void	ft_delnode(t_lexer *temp, t_lexer  **lexer_list);
t_lexer	*ft_lexernew(char *str, int token); //en verdad es del lexer
void	ft_lexeradd_back(t_lexer **lst, t_lexer *new); //en verdad es del lexer
int (*command_handler (char *str))(t_mshell *minishell, t_parser *commands);
void	ft_parseradd_back(t_parser **lst, t_parser *new);
t_parser	*ft_parsernew();

void free_lexer_list(t_lexer *list);
void free_string_array(char **array);
void free_parser_list(t_parser *list);

#endif // HEADER_H