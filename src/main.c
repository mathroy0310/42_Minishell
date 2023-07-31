/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   main.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/07/31 15:51:18 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"


/*
	TODO parsing -> cmds -> shell redirection -> flags - quotes - env - pipes
*/



int	main(void)
{	
	//t_minishell minishell;

	//minishell.env->value = getenv("PATH");

	//getenv tests
	printf("PATH : %s\n", getenv("PATH"));
   	printf("HOME : %s\n", getenv("HOME"));
   	printf("ROOT : %s\n", getenv("ROOT"));
	//exec_env(minishell.env);
	
	printf("PWD");
	exec_pwd();
	return (0);
}
