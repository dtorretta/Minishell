/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_mig.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:29:16 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/01 17:46:23 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_MIG_H
# define HEADER_MIG_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

/*******STRUCTURES*******/
typedef enum s_tokens
{
	WORD,
	PIPE,
	GREAT,
	GREAT_GREAT,
	LESS,
	HERE_DOC, // antes era LESS_LESS
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

struct	s_parser;
struct	s_mshell;

//ESTA ES LA ESTRUCTURA FINAL QUE SE PASA AL EXECUTABLE
typedef struct s_mshell
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_parser			*commands;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*old_pwd;
	int						pipes; //ver si es necesario. Hasta hoy 17.6 no ha sido utilizada
	int						*pid;
	int						in_cmd; // nuevo (creamos para señalar que hay un comando activo)
	bool					heredoc;
	bool					reset;
}	t_mshell; //t_tools;

typedef struct s_parser
{
	char					**str;
	int						(*builtins_handler)(t_mshell *, struct s_parser *); //Es un puntero a la funcion builtin que tiene 2 argumentos: Un puntero a t_mshell y Un puntero a t_parser
	int						num_redirections;
	char					*hd_file_name; //?
	t_lexer					*redirections;
	struct s_parser			*next;
	struct s_parser			*prev;
}	t_parser; //t_simple_cmds;

/****INITIALIZATION****/

/*-Enviroment-*/
void		get_pwd(t_mshell *data);
char		*get_path(char **envp);
int			handle_envp(t_mshell *data);
/*-Utils-*/
char		**dup_str(char **array);
int			init_data(t_mshell *data);
int			reset_data(t_mshell *data);
/*-Signals-*/
void		init_signals(void);
void		handle_ctrl_backslash(int sig); //Chequear si se necesita por fuera
void		handle_ctrl_c(int sig); //Chequear si se necesita por fuera

/*******LEXER*******/

/*-Token handling-*/
int			lexer(t_mshell *data);
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
t_lexer		*lexer_delete_one(t_lexer **list);
void		lexer_delete_first(t_lexer **list);
void		lexer_delete_specific(t_lexer **list, int node_index);
void		lexer_delete_all(t_lexer **list);

/*******PARSER*******/

void		parser(t_mshell *minishell);
int			(*builtins_handler(char *str))(t_mshell *minishell, t_parser *commands);
t_parser	*parser_new_node(t_mshell *minishell);
void		parser_add_last(t_parser **head, t_parser *new);
void		ft_delnode(t_lexer *temp, t_lexer **head);
void		free_lexer_list(t_lexer *list);
void		free_string_array(char **array);

/*******BUILSTINS*******/

int			mini_echo(t_mshell *minishell, t_parser *commands);
int			mini_env(t_mshell *minishell, t_parser *commands);
int			mini_exit(t_mshell *minishell, t_parser *commands);
void		free_minishell(t_mshell *minishell);
int			mini_pwd(t_mshell *minishell, t_parser *commands);

/*******EXPANDER*******/

/*-Utils-*/
char		*remove_single_quote(char *str);


/*******ERROR HANDLING*******/

int			handle_error(t_mshell *data, int error);

#endif
