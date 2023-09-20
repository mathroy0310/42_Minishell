/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   libft.h                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2022/10/17 12:41:20 by maroy                                    */
/*   Updated: 2023/09/16 21:20:34 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1024

// linked list
typedef struct s_list
{
	char			*content;
	char			*key;
	char			*value;
	struct s_list	*next;
}					t_list;

// string.h
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memalloc(size_t size);
size_t				ft_strlen(const char *s);
// Returns a pointer to the first occurrence of character in the C string str.
// The terminating null-character is considered part of the C string. Therefore,
// it can also be located in order to retrieve a pointer to the end of a string.
char				*ft_strchr(char *save, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				ft_bzero(void *s, size_t n);

// stdlib.h
void				*ft_calloc(size_t count, size_t size);
char				*ft_itoa(int n);
int					ft_atoi(const char *str);

// ctype.h
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

// Put[] functions
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);

char				**ft_split(char const *s, char c);
char				*ft_strdup(const char *s1);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);

// Lst
t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
// GNL
char				*get_next_line(int fd);

//* Mes Fonctions *//

// lst

void				ft_lstpush(t_list **lst, t_list *new);

// is
int					ft_iscntrl(int c);
int					ft_isgraph(int c);
int					ft_ispunct(int c);
int					ft_isxdigit(int c);
int					ft_isspace(int c);

//	Math
double				ft_pow(double x, double y);
double				ft_sqrt(double x);
double				ft_abs(double x);
double				ft_floor(double x);
double				ft_ceil(double x);

//	Memory
void				*ft_malloc(size_t size);
void				*ft_realloc(void *ptr, size_t size);
void				*ft_free(void *ptr);
void				ft_free_tab(char **tab);

// string.h
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strcat(char *dest, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strtok(char *str, const char *delim);

// atol , atof
float				ft_atof(const char *str);
long				ft_atol(const char *str);

// custom
int					ft_count_char(char *s, char c);
int					ft_count_words(char *str, char *charset);
int					ft_tablen(char **env);
char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_strjoin_char(char *s, char c);
uint8_t				ft_strequal(const char *s1, const char *s2);

int					is_white_space(char *buff);
// Random
int					ft_rand(int min, int max);

//	doubly list , dlist
typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

t_dlist				*ft_dlstnew(void *content);
void				ft_dlstadd_back(t_dlist **alst, t_dlist *new);
void				ft_dlstadd_front(t_dlist **alst, t_dlist *new);
t_dlist				*ft_dlstlast(t_dlist *lst);
t_dlist				*ft_dlstfirst(t_dlist *lst);
void				ft_dlstclear(t_dlist **lst, void (*del)(void *));
void				ft_dlstdelone(t_dlist *lst, void (*del)(void *));
void				ft_dlstpop_front(t_dlist **head, void (*del)(void *));
void				ft_dlstpop_back(t_dlist **head, void (*del)(void *));
void				ft_dlstclearback_addr(t_dlist **lst, void (*del)(void **));

#endif
