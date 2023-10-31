/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   main.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/10/28 16:22:40 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "minishell.h"

t_global	*g_global;

/*
! Etape 1 : Lexer (Analyseur lexical)

1.	Analyse du texte : Le lexer parcourt le code source caractère par caractère.

2.	Reconnaissance des motifs : Le lexer identifie des motifs dans le texte,
	comme les espaces, les mots, les opérateurs, etc.

3.	Création de tokens : Chaque fois qu'un motif significatif est trouvé,
	un token est créé. Par exemple, "echo $USER >> username.txt" pourrait
	être divisé en quatres tokens : "echo", "$USER ", ">>", "username.txt".

4.	Gestion des erreurs : Si le lexer rencontre un caractère ou un motif
	qui ne correspond à aucun token valide.

! Etape 2: Parser (Analyseur syntaxique)

1.	Définition de la grammaire :La création d'une grammaire formelle qui
	décrit comment les tokens peuvent être combinés pour former
	des expressions valides.

2.	Création de l'AST : Le parser construit un arbre de syntaxe abstraite
	en utilisant les tokens. Chaque nœud de l'arbre représente
	une expression ou une déclaration syntaxique,
	et les relations entre les nœuds
	représentent la structure du code.

3.	Vérification de la validité : Pendant la création de l'AST,
	assurez-vous que les combinaisons de tokens suivent la grammaire définie,
	sinon signalez des erreurs syntaxiques.

4.	Gestion des erreurs : Gestion de toutes les erreurs syntaxiques
	rencontrées lors de l'analyse

! Etape 3: Execution

1.	Gestion des commandes intégrées : Implémentation des commandes intégrées
	telles que `cd`, `pwd`, `echo`, `unset`, `export`, `env`, `exit`, etc.

2.	Gestion des processus : Création de child process  avec `fork()`
	pour exécuter des commandes externes.

	Utilisation de `execve()` pour exécuter des commandes externes
	dans ces child process.

3.	Gestion des pipes : Prise en charge des commandes avec des pipes (`|`),
	en créant et en utilisant des pipes pour rediriger
	les flux de données entre les commandes.

4.	Gestion des fichiers d'entrée/sortie : Gestion de la redirection
	d'entrée (`<`), de sortie (`>`) et (`>>`)

5. Gestion des erreurs : Gestion de toutes les erreurs potentielles
	avec des messages d'erreur informatifs pour guider les utilisateurs.

*/

void	quit_minishell(char *buff)
{
	ft_putstr_nl("exit");
	free(buff);
	exit(g_global->exit_status);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	return (minishell_master(env));
}
