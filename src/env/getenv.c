/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   getenv.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 16:14:52 by maroy                                    */
/*   Updated: 2023/08/04 13:33:18 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"



int		env_value_len(const char *env)
{
	int		i;
	int		size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		i++;
		size_name++;
	}
	return (size_name);
}

char		*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFFER_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*env_value(char *env)
{
	int		i;
	int		j;
	char	*env_value;

	env_value = ft_malloc(sizeof(char) * env_value_len(env) + 1);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}

char* get_env_value(char* arg, t_env* env) 
{
    char env_name[BUFFER_SIZE];
    char* env_val;

    env_val = (char*)ft_malloc(sizeof(char));
    ft_strcpy(env_val, "");

    while (env && env->value) 
    {
        get_env_name(env_name, env->value);
        if (ft_strcmp(arg, env_name) == 0) 
        {
            free(env_val);
            env_val = env_value(env->value);
            return env_val;
        }
        env = env->next;
    }

    return env_val;
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		tmp = env;
		env = env->next;
		ft_free(tmp->value);
		ft_free(tmp);
	}
	ft_free(env->value);
	ft_free(env);
}

void init_env(t_minishell *minishell, char **envp )
{
    t_env *env;
    t_env *tmp;
    int i;
    
    env = ft_malloc(sizeof(t_env));
    env->value = ft_strdup(envp[0]);
    env->next = NULL;
    minishell->env = env;
    i = 1;
    while (envp && envp[0] && envp[i])
    {
        tmp = ft_malloc(sizeof(t_env));
        tmp->value = ft_strdup(envp[i]);
        tmp->next = NULL;
        env->next = tmp;
        env = tmp;
        i++;
    }
}