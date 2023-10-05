/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   parser.h                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/29 20:10:28 by maroy                                    */
/*   Updated: 2023/10/05 15:11:33 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
 * -- Local Includes --
 */
# include "lexer.h"
# include "minishell.h"

typedef struct s_parser
{
	t_lexer			*lexer;
	t_token			*curr_token;
	t_token			*prev_token;
}					t_parser;

typedef struct s_index
{
	int				k;
	int				l;
	int				m;
}					t_index;

typedef enum e_ast_type
{
	pipe_ast,
	arg_ast
}					t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	struct s_ast	**pipecmd_values;
	int				pipecmd_size;
	t_token			**args;
	int				redir_nbr;
	int				args_size;
}					t_ast;

/*
 * parser.c *
 */

t_ast				*parse_pipe(t_parser *parser);

/*
 * parser_utils.c *
 */

t_parser			*init_parser(t_lexer *l);
int					is_redirect(t_token *t);
int					syntax_error(t_parser *p);
char				*get_stop_word(t_parser *p);

t_parser			*init_parser(t_lexer *lexer);

/*
 * ast.c *
 */

void				init_ast(t_ast *ast, t_ast_type type);
t_cmd				*parse_pipeline_to_cmd(t_ast *ast);

/*
 * realloc_ast.c *
 */

t_token				**realloc_ast_args(t_ast *ast, int size);
t_ast				**realloc_ast_node(t_ast *ast, int size);
t_token				*check_token(t_parser *p, t_ast *ast);

/*
 * free.c *
 */

t_ast				*free_tree(t_ast *ast);
void				free_parser(t_parser *parser);
void				free_parser_helper(t_parser *parser, int i);
void				free_cmd(t_cmd *cmd);

#endif
