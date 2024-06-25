#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Assuming these functions and structs are defined elsewhere
typedef struct s_lexer {
    char *value;
    int type;
    struct s_lexer *next;
} t_lexer;

#define WORD 1

int check_token(char c) {
    // Dummy function, replace with actual implementation
    return (c == ';' || c == '|');
}

int ft_iswhitespace(char c) {
    // Check if character is a whitespace
    return isspace(c);
}

t_lexer *add_node(char *value, int type, t_lexer **lexer_list) {
    // Dummy function to simulate adding a node
    t_lexer *new_node = malloc(sizeof(t_lexer));
    if (!new_node) return NULL;
    new_node->value = value;
    new_node->type = type;
    new_node->next = NULL;
    if (!*lexer_list) {
        *lexer_list = new_node;
    } else {
        t_lexer *temp = *lexer_list;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    return new_node;
}

char *ft_substr(const char *str, int start, int len) {
    // Function to create a substring
    char *substr = malloc(len + 1);
    if (!substr) return NULL;
    strncpy(substr, str + start, len);
    substr[len] = '\0';
    return substr;
}

int	copy_quoted_content(char *str, int start, char *cleaned_word, int *i)
{
	char	quote_type;
	int	len;

	len = 1;
	quote_type = str[start];
	while (str[start + len] && str[start + len] != quote_type)
	{
		cleaned_word[(*i)] = str[start + len];
		(*i)++;
		len++;
	}
	if (str[start + len] == quote_type)
		len++;
	return (len);
}

int	handle_word(char *str, int start, t_lexer **lexer_list)
{
	char	*cleaned_word;
	int		i;
	int		len;

	len = 0;
	i = 0;
	cleaned_word = (char *)malloc(strlen(str) + 1);
	if (!cleaned_word)
		return (-1);
	while (str[start + len] && (!check_token(str[start + len])
			&& !ft_iswhitespace(str[start + len])))
	{
		if (str[start + len] == '\"' || str[start + len] == '\'')
			len += copy_quoted_content(str, start + len, cleaned_word, &i);
		else
			cleaned_word[i++] = str[start + len++];
	}
	cleaned_word[i] = '\0';
	if (!add_node(strdup(cleaned_word), WORD, lexer_list))
	{
		free(cleaned_word);
		return (-1);
	}
	free(cleaned_word);
	return (len);
}

/*
char	*clean_quotes(char *str, int start, int len)
{
	char	*word_start;
	char	*word_end;

	word_start = ft_substr(str, start, len);
	word_end = word_start + len;

	if ()

}*/

/*
int	handle_word(char *str, int start, t_lexer **lexer_list)
{
	int		len;
	int		quote_len;
	char	*word_start;

	len = 0;
	quote_len = 0;
	word_start = "";
	while (str[start + len] && (!check_token(str[start + len])
			&& !ft_iswhitespace(str[start + len])))
	{
		quote_len = skip_quotes(str, start + len, '\"');
		if (quote_len == 0)
			quote_len = skip_quotes(str, start + len, '\'');
		if (quote_len > 0)
			len += quote_len;
		else
			len++;
	}
	word_start = clean_quotes(str, start, len);

    if (!add_node(ft_substr(str, start, len), WORD, lexer_list)) {
        return -1;
    }
    return len;
}*/

/*
int handle_word(char *str, int start, t_lexer **lexer_list) {
    int len = 0;
    int quote_len;
    char *word_start;
    char *word_end;
    char *word;
    char quote_char;

    while (str[start + len] && (!check_token(str[start + len]) && !ft_iswhitespace(str[start + len]))) {
        quote_len = skip_quotes(str, start + len, '\"');
        if (quote_len == 0) {
            quote_len = skip_quotes(str, start + len, '\'');
        }
        if (quote_len > 0) {
            len += quote_len;
        } else {
            len++;
        }
    }

    word = ft_substr(str, start, len);

    // Remove surrounding quotes if present
    word_start = word;
    word_end = word + len;

    // Check for double or single quotes and remove them
    while ((*word_start == '\"' || *word_start == '\'') && (*(word_end - 1) == '\"' || *(word_end - 1) == '\'')) {
        quote_char = *word_start;
        if (*word_start == *(word_end - 1)) {
            word_start++;
            word_end--;
            // Remove any additional quotes at the start and end
            while (*word_start == quote_char && *(word_end - 1) == quote_char && word_start < word_end) {
                word_start++;
                word_end--;
            }
        } else {
            break;
        }
    }
    *word_end = '\0';

    if (!add_node(strdup(word_start), WORD, lexer_list)) {
        free(word); // Free the original substring allocation
        return -1;
    }
    free(word); // Free the original substring allocation
    return len;
}*/


void print_lexer_list(t_lexer *lexer_list) {
    t_lexer *temp = lexer_list;
    while (temp) {
        printf("Token: %s\n", temp->value);
        temp = temp->next;
    }
}

int main() {
    char *input = "\"\"\"hello\"8\"\" 'another test' plain_text";
    t_lexer *lexer_list = NULL;
    int pos = 0;
    int len;

    printf("Input: %s\n", input);

    while (input[pos]) {
        while (ft_iswhitespace(input[pos])) {
            pos++;
        }
        if (input[pos]) {
            len = handle_word(input, pos, &lexer_list);
            if (len == -1) {
                fprintf(stderr, "Error handling word\n");
                return 1;
            }
            pos += len;
        }
    }

    print_lexer_list(lexer_list);

    // Free lexer_list
    t_lexer *temp;
    while (lexer_list) {
        temp = lexer_list;
        lexer_list = lexer_list->next;
        free(temp->value);
        free(temp);
    }

    return 0;
}
