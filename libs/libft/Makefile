# **************************************************************************** #
#                                                                              #
#                                                      ██   ██ ██████          #
#    Makefile                                          ██   ██      ██         #
#                                                      ███████  █████          #
#    By: maroy <maroy@student.42.qc>                        ██ ██              #
#                                                           ██ ███████.qc      #
#    Created: 2023/07/14 21:56:43 by maroy                                     #
#    Updated: 2023/08/24 16:29:26 by maroy            >(.)__ <(.)__ =(.)__     #
#                                                      (___/  (___/  (___/     #
# **************************************************************************** #

#--- PROGRAM NAME ---#
NAME		=	libft.a

#--- HEADERS ---#
HEADER_DIR		= inc/
HEADER_SRC		= libft.h
HEADER			= $(addprefix $(HEADER_DIR), $(HEADER_SRC))

#--- SOURCES ---#
SRC_DIR		= src/
SRC_SRC		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
			ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c ft_strtrim.c \
			ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c \
			ft_lstadd_front.c ft_lstclear.c ft_lstmap.c ft_lstlast.c ft_lstsize.c \
			ft_lstnew.c ft_lstadd_back.c ft_lstdelone.c ft_lstiter.c \
			ft_dlstnew.c ft_dlstadd_back.c ft_dlstadd_front.c ft_dlstlast.c ft_dlstfirst.c \
			ft_dlstclear.c ft_dlstdelone.c ft_dlstpop_front.c ft_dlstpop_back.c ft_dlstclearback_addr.c\
			ft_free.c ft_free_arr.c ft_strtok.c ft_abs.c ft_atof.c ft_atol.c ft_floor.c ft_ceil.c ft_free_arr.c \
			ft_iscntrl.c ft_isgraph.c ft_ispunct.c ft_isxdigit.c ft_malloc.c ft_pow.c ft_rand.c ft_realloc.c ft_sqrt.c \
			ft_strcat.c ft_strcpy.c ft_strncpy.c ft_isspace.c ft_strcmp.c ft_count_char.c ft_count_words.c 
SRC			= $(addprefix $(SRC_DIR), $(SRC_SRC))

#--- OBJECTS ---#
BIN_DIR     = bin/
BIN         = $(patsubst $(SRC_DIR)%.c,bin/%.o,$(SRC))
 
 
#--- COMPILATION FLAG ---#
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I./inc

#--- CLEANING ---#
$(RM) 	 = rm -rf

#--- RULES ---#
bin/%.o: $(SRC_DIR)%.c  $(HEADER)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
 
$(NAME): $(BIN)
	@ar rcs $(NAME) $(BIN)
 
$(BINDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BIN_DIR)
 
fclean: clean
	@$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re bonus