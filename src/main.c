/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   main.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/09/03 13:57:30 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_global	*g_global;

/*
! Etape 1 : Lexer (Analyseur lexical)

1.	Analyse du texte : Le lexer parcourt le code source caractère par caractère.

2.	Reconnaissance des motifs : Le lexer identifie des motifs dans le texte,
	comme les espaces, les mots, les opérateurs, etc.

3.	Création de tokens : Chaque fois qu'un motif significatif est trouvé,
	un token est créé. Par exemple, "ls -l" pourrait être divisé
	en trois tokens : "ls", "-", "l".

! Etape 2: Parser (Analyseur syntaxique)

1.	Définition de la grammaire : Vous définissez une grammaire formelle qui décrit
	comment les tokens peuvent être combinés pour former des expressions valides,
	tout comme précédemment.

2.	Création de l'AST : Le parser construit un arbre de syntaxe abstraite
	en utilisant les tokens. Chaque nœud de l'arbre représente
	une expression ou une déclaration syntaxique,
		et les relations entre les nœuds
	représentent la structure du code.

*/

int	main(int argc, char **argv, char **env)
{
	return (minishell_master(argc, argv, env));
}
