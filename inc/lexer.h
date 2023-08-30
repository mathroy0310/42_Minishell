/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:26:07 by maroy             #+#    #+#             */
/*   Updated: 2023/08/29 20:43:59 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

//  Libft
# include "../libs/libft/inc/libft.h"

typedef enum e_token_type
{
	pip,
	great,
	greater,
	less,
	here_doc,
	id,
	illegal,
	eof
}			t_token_type;

typedef struct s_lexer
{
	char	*buffer;
	int		bufsize;
	int		curpos;
	int		readpos;
	char	c;
	int		multi_line;
	int		is_quoted;
}				t_lexer;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				is_quoted;
}				t_token;

/*
* lexer.c *
*/

void		readchar(t_lexer *lexer);
t_token		*ret_str(t_lexer *lexer, char *s, int type);
t_token		*get_next_token(t_lexer *lexer);

/*
* get_next_token.c *
*/

char	*tokenize_text(t_lexer *lexer, char *str);
t_token	*string_token(t_lexer *lexer);

/*
* lexer_utlis.c *
*/

int		valid_envar(char c);
char	*ft_getenv(char *str);
char	*envar_token(t_lexer *lexer);

/*
* utils.c *
*/

t_lexer		*init_lexer(t_lexer	*lexer);
void		print_msg(char *str, char *var);
t_token		*init_token(t_token_type type, char *str, t_lexer *lexer);
int			peek_char(t_lexer *lexer);
int			multi_lines(t_lexer *lexer, char c);

#endif