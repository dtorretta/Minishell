/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_mig.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:29:16 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/11 16:47:39 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_MIG_H
# define HEADER_MIG_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
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
	struct s_simple_cmds	*simple_cmds;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*old_pwd;
	int						pipes; //ver si es necesario
	int						*pid;
	bool					heredoc;
	bool					reset;
	int error_code;
}	t_mshell;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_mshell *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

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

#endif
