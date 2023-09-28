# **************************************************************************** #
#                                                                              #
#                                                      ██   ██ ██████          #
#    Makefile                                          ██   ██      ██         #
#                                                      ███████  █████          #
#    By: maroy <maroy@student.42.qc>                        ██ ██              #
#                                                           ██ ███████.qc      #
#    Created: 2023/07/27 15:41:11 by maroy                                     #
#    Updated: 2023/09/27 14:33:55 by maroy            >(.)__ <(.)__ =(.)__     #
#                                                      (___/  (___/  (___/     #
# **************************************************************************** #

#--- PROGRAM NAME ---#

NAME				=	minishell

#--- LIBRARIES AND HEADERS ---#

HEADER_FILES		= 	minishell.h defines.h  lexer.h execution.h builtins.h

HEADERS				= 	$(addprefix $(INCDIR)/, $(HEADER_FILES))

LIBFT				=	${LIBDIR}/libft

MAKELIB				=	${MAKE} -C ${LIBFT}

SLIB_LIBFT			=	${LIBFT}/libft.a

TERMCAP 			= 	termcap-1.3.1

TERMCAP_DIR 		= 	./libs/termcap

LIBRLINE 			= 	readline-8.2

LIBRLINE_DIR 		= 	./libs/readline/

SLIB_RLINE 			= 	$(LIBRLINE_DIR)libreadline.a

#--- COMMAND VARIABLES ---#

CC					=	gcc

CFLAGS 				=	-Wall -Wextra -Werror -std=c17

RLFLAGS				=	-lreadline -lcurses

TIFLAGS				=	-ltermcap

MK					=	mkdir -p

RM					=	rm -rf


#--- SOURCE, INCLUDE AND BINARIES DIRECTORIES ---#

INCDIR				=	inc

LIBDIR				=	libs

SRC_MAIN_DIR 		= 	src

SRC_PARSING_DIR 	= 	$(SRC_MAIN_DIR)/parsing

SRC_EXECUT_DIR		= 	$(SRC_MAIN_DIR)/execution

SRC_BUILTINS_DIR 	= 	$(SRC_EXECUT_DIR)/builtins

SRC_DIR 			=	$(SRC_MAIN_DIR) $(SRC_PARSING_DIR) $(SRC_EXECUT_DIR) $(SRC_BUILTINS_DIR)

BINDIR				=	bin

#--- SOURCES ---#

SRCS_MAIN			=	main.c debug.c  minishell.c

SRCS_PARSING 		= 	lexer.c parser.c utils.c free.c get_next_token.c lexer_utils.c parser_utils.c ast.c ast_realloc.c

SRCS_EXECUT			=	exec_main.c exec_reg_cmd.c free.c handle_pipes.c handle_pipes_utils.c exec_multi_cmd.c exec_utils.c signals.c error.c redirections.c here_doc.c here_doc_utils.c

SRCS_BUILTINS		= 	builtins_utils.c builtins.c cd_utils.c cd.c echo.c env.c exit.c export_utils.c export.c pwd.c unset.c 

#-- PREFIXED SOURCES --#

SRC_M				=	$(addprefix $(SRC_MAIN_DIR)/, $(SRCS_MAIN))

SRC_P				=	$(addprefix $(SRC_PARSING_DIR)/, $(SRCS_PARSING))

SRC_E				=	$(addprefix $(SRC_EXECUT_DIR)/, $(SRCS_EXECUT))

SRC_B				=	$(addprefix $(SRC_BUILTINS_DIR)/, $(SRCS_BUILTINS))

SRC 				=	$(SRC_M) $(SRC_P) $(SRC_E) $(SRC_B)

BIN     			=	$(patsubst $(SRCDIR)%.c,bin/%.o,$(SRC))

#--- RULES ---#

bin/%.o		: $(SRCDIR)%.c  $(HEADERS)
	@mkdir -p $(@D)
	@printf "\r${DARKGRAY}Compiling : $(@F) ... ${DEFAULT}\033[K"
	@$(CC) $(CFLAGS) -c $< -o $@ 

all			: readline termcap ${NAME}

debug		: CFLAGS += -g3 -fsanitize=address -DDEBUG_FLAG=1 
debug		: re

termcap		:
	@#!/bin/bash
	@set -e
	@if [ ! -f $(TERMCAP_DIR)/inc/termcap.h ]; then \
		echo "${BLUE}Installing Termcap ... ${DARKGRAY}"; \
		mkdir -p $(TERMCAP_DIR); \
		curl -O https://ftp.gnu.org/gnu/termcap/$(TERMCAP).tar.gz > /dev/null 2>&1; \
		tar -xf $(TERMCAP).tar.gz > /dev/null 2>&1; \
		rm -rf $(TERMCAP).tar.gz; \
		cd $(TERMCAP) && ./configure > /dev/null 2>&1 && make > /dev/null 2>&1; \
		mv libtermcap.a ../libs/termcap > /dev/null 2>&1; \
		mkdir ../libs/termcap/inc > /dev/null 2>&1; \
		mv ./*.h ../libs/termcap/inc > /dev/null 2>&1; \
		cd .. && rm -rf $(TERMCAP); \
		echo "${BLUE}Termcap successfully installed 🗄${DEFAULT}"; \
	fi

readline	:
	@#!/bin/bash
	@set -e
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
	@echo "\r${GREEN}${NAME} successfully created. 📂${DEFAULT}"

clean		:
	@${MAKELIB} clean
	@${RM} ${BINDIR}
	@echo "${YELLOW}${NAME} binary files successfully removed 🗑${DEFAULT}"

fclean		:	clean

	@${RM} ${NAME}
	@echo "${RED}${NAME} executable successfully removed 🗑${DEFAULT}"

re	 		:	fclean all

bonus		:	all

norm		:
	@echo "$(DARKGRAY)norminette! $(DEFAULT)"
	@norminette $(INCDIR) $(SRCDIR) $(LIBFT)/src $(LIBFT)/inc



#--- PHONY ---#
.PHONY	 	:	all clean fclean re readline norm bonus

#--- COLORS ---#

RED					= \033[1;31m

GREEN				= \033[1;32m

BLUE				= \033[1;34m

YELLOW				= \033[1;33m

DARKGRAY			= \033[1;30m

DEFAULT 			= \033[1;30m
