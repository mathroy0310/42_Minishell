# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maroy <maroy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 15:41:11 by maroy             #+#    #+#              #
#    Updated: 2023/08/29 22:16:09 by maroy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--- PROGRAM NAME ---#

NAME	=	minishell

#--- COLORS ---#

RED		= \033[1;31m

GREEN	= \033[1;32m

BLUE	= \033[1;34m

YELLOW	= \033[1;33m

DARKGRAY= \033[1;30m

DEFAULT = \033[1;30m

#--- LIBRARIES AND HEADERS ---#

HEADER_FILES	= minishell.h defines.h  lexer.h

HEADERS			= $(addprefix $(INCDIR)/, $(HEADER_FILES))

LIBFT			=	${LIBDIR}/libft

MAKELIB			=	${MAKE} -C ${LIBFT}

SLIB_LIBFT		=	${LIBFT}/libft.a

TERMINFO 		= termcap-1.3.1

TERMINFO_DIR 	= ./libs/termcap

LIBRLINE 		= readline-8.2

LIBRLINE_DIR 	= ./libs/readline/

SLIB_RLINE 		= $(LIBRLINE_DIR)libreadline.a

#--- COMMAND VARIABLES ---#

CC		=	gcc

CFLAGS 	=	-Wall -Wextra -Werror -std=c17 -ltermcap -g3 -fsanitize=address

RLFLAGS	=	-lreadline -lcurses

MK		=	mkdir -p

RM		=	rm -rf

#--- SOURCE, INCLUDE AND BINARIES DIRECTORIES ---#

INCDIR	=	inc

LIBDIR	=	libs

SRCDIR	=	src

BINDIR	=	bin

#--- SOURCES ---#
SRCS	=	main.c debug.c signals.c minishell.c\
			parsing/lexer.c parsing/parser.c parsing/utils.c parsing/free.c parsing/get_next_token.c\
			parsing/lexer_utils.c parsing/parser_utils.c parsing/ast.c parsing/ast_realloc.c \
			builtins/pwd.c builtins/env.c \
			env/getenv.c

SRC		= $(addprefix $(SRCDIR)/, $(SRCS))

BIN     = $(patsubst $(SRCDIR)%.c,bin/%.o,$(SRC))

#--- RULES ---#

bin/%.o		: $(SRCDIR)%.c  $(HEADERS)
	@mkdir -p $(@D)
	@echo "${DARKGRAY}Compiling : $(@F) ... ${DEFAULT}"
	@$(CC) $(CFLAGS) -c $< -o $@

all			: readline termcap ${NAME}

termcap:
	@if [ ! -f $(TERMINFO_DIR)/libtermcap.a ]; then \
		echo "${BLUE}Installing Termcap ... ${DARKGRAY}"; \
		mkdir -p $(TERMINFO_DIR); \
		curl -O https://ftp.gnu.org/gnu/termcap/$(TERMINFO).tar.gz > /dev/null 2>&1; \
		tar -xf $(TERMINFO).tar.gz > /dev/null 2>&1; \
		rm -rf $(TERMINFO).tar.gz; \
		cd $(TERMINFO) && ./configure > /dev/null 2>&1 && make > /dev/null 2>&1; \
		mv libtermcap.a ../libs/termcap > /dev/null 2>&1; \
		mkdir ../libs/termcap/inc > /dev/null 2>&1; \
		mv ./*.h ../libs/termcap/inc > /dev/null 2>&1; \
		cd .. && rm -rf $(TERMINFO); \
		echo "${BLUE}Termcap successfully installed 🗄${DEFAULT}"; \
	fi

readline	:
	@if [ ! -f ./libs/readline/libreadline.a ]; then \
		echo "${BLUE}Installing Readline ... ${DARKGRAY}"; \
		mkdir -p $(LIBRLINE_DIR); \
		curl -O https://ftp.gnu.org/gnu/readline/$(LIBRLINE).tar.gz > /dev/null 2>&1; \
		tar -xf $(LIBRLINE).tar.gz > /dev/null 2>&1; \
		rm -rf $(LIBRLINE).tar.gz; \
		cd $(LIBRLINE) && bash configure > /dev/null 2>&1 && make > /dev/null 2>&1;\
		mv ./libreadline.a ../libs/readline > /dev/null 2>&1; \
		mkdir ../libs/readline/inc > /dev/null 2>&1; \
		mv ./*.h ../libs/readline/inc > /dev/null 2>&1; \
		rm -rf ../$(LIBRLINE); \
		echo "${BLUE}Readline successfully created 🗄${DEFAULT}"; \
	fi

${NAME}		:	${BIN}
	@${MAKELIB}
	@${CC} ${CFLAGS} ${BIN} ${RLFLAGS} ${SLIB_RLINE} ${SLIB_LIBFT} -o ${NAME} 
	@echo "${GREEN}Minishell successfully created. 📂${DEFAULT}"

clean		:
	@${MAKELIB} clean
	@${RM} ${BINDIR}
	@echo "${YELLOW}Minishell binary files successfully removed 🗑${DEFAULT}"

fclean		:	clean
	@${MAKELIB} fclean
	@${RM} ${NAME}
	@echo "${RED}Minishell executable successfully removed 🗑${DEFAULT}"

re	 		:	fclean all

bonus		:	all

norm		:
	@echo "$(DARKGRAY)norminette! $(DEFAULT)"
	@norminette $(INCDIR) $(SRCDIR) $(LIBFT)/src $(LIBFT)/inc

#--- PHONY ---#
.PHONY	 	:	all clean fclean re readline norm bonus