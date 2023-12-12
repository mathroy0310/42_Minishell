# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maroy <maroy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 15:41:11 by maroy             #+#    #+#              #
#    Updated: 2023/12/11 17:53:53 by maroy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--- PROGRAM NAME ---#

NAME				=	minishell

#--- LIBRARIES AND HEADERS ---#

LIBFT				=	${LIBDIR}/libft

MAKELIB				=	${MAKE} -C ${LIBFT}


LIBFT				=	libft

LIBFT_DIR			= 	./libs/libft

SLIB_LIBFT			=	${LIBFT_DIR}/libft.a

TERMCAP 			= 	termcap-1.3.1

TERMCAP_DIR 		= 	./libs/termcap

LIBRLINE 			= 	readline-8.2

LIBRLINE_DIR 		= 	./libs/readline/

SLIB_RLINE 			= 	$(LIBRLINE_DIR)libreadline.a

#--- COMMAND VARIABLES ---#

CC					=	gcc

CFLAGS 				=	-Wall -Wextra -Werror -std=c17 -I${INCDIR}

RLFLAGS				=	-L${LIBRLINE_DIR} -lreadline -lcurses -I${LIBRLINE_DIR}/inc

VALGFLAGS = --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=rl_supp.txt

LIBFTFLAGS			= 	-L${LIBFT_DIR} -lft -I${LIBFT_DIR}/inc

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

SRCS_MAIN			=	main.c \
						debug.c \
						debug_utils.c \
						minishell.c \
						free.c \
						signals.c \
						utils.c \
						readline.c \

SRCS_PARSING 		= 	lexer.c \
						parser.c \
						utils.c \
						free.c \
						get_next_token.c \
						lexer_utils.c \
						parser_utils.c \
						init.c \
						ast.c \
						ast_realloc.c

SRCS_EXECUT			=	error.c \
						exec_main.c \
						exec_multi.c \
						exec_simple.c \
						exec_regular.c \
						exec_utils.c \
						free.c \
						utils.c \
						redirections.c \
						

SRCS_BUILTINS		= 	builtins.c \
						builtins_utils.c \
						cd.c \
						cd_utils.c \
						echo.c \
						env.c \
						exit.c \
						export_utils.c \
						export.c \
						pwd.c \
						unset.c 

#-- PREFIXED SOURCES --#

SRC_M				=	$(addprefix $(SRC_MAIN_DIR)/, $(SRCS_MAIN))

SRC_P				=	$(addprefix $(SRC_PARSING_DIR)/, $(SRCS_PARSING))

SRC_E				=	$(addprefix $(SRC_EXECUT_DIR)/, $(SRCS_EXECUT))

SRC_B				=	$(addprefix $(SRC_BUILTINS_DIR)/, $(SRCS_BUILTINS))

SRC 				=	$(SRC_M) $(SRC_P) $(SRC_E) $(SRC_B)

BIN     			=	$(patsubst $(SRCDIR)%.c,bin/%.o,$(SRC))

#--- RULES ---#

bin/%.o		: $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "\r${DARKGRAY}Compiling : $(@F) ... ${DEFAULT}\033[K"
	@$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY		:	all
all			: ${NAME}

.PHONY		:	debug
debug		: CFLAGS += -g3 -DDEBUG=1 #-fsanitize=address 
debug		: re

${SLIB_LIBFT}	:
	@echo "${BLUE}Installing Libft ... ${DARKGRAY}"; \
	$(MK) $(LIBFT_DIR); \
	git clone https://github.com/mathroy0310/42_libft.git $(LIBFT_DIR) > /dev/null 2>&1; \
	make -C $(LIBFT_DIR) > /dev/null 2>&1; \
	echo "${BLUE}Libft successfully installed 🗄${DEFAULT}";

${SLIB_RLINE}	:
	@echo "${BLUE}Installing Readline ... ${DARKGRAY}"; \
	$(MK) $(LIBRLINE_DIR); \
	curl -O https://ftp.gnu.org/gnu/readline/$(LIBRLINE).tar.gz > /dev/null 2>&1; \
	tar -xf $(LIBRLINE).tar.gz > /dev/null 2>&1; \
	rm -rf $(LIBRLINE).tar.gz; \
	cd $(LIBRLINE) && bash configure > /dev/null 2>&1 && make > /dev/null 2>&1;\
	mv ./libreadline.a ../libs/readline > /dev/null 2>&1; \
	mkdir ../libs/readline/inc > /dev/null 2>&1; \
	mv ./*.h ../libs/readline/inc > /dev/null 2>&1; \
	rm -rf ../$(LIBRLINE); \
	echo "${BLUE}Readline successfully created 🗄${DEFAULT}";

${NAME}		:	${SLIB_RLINE} ${SLIB_LIBFT} ${BIN} 
	@${CC} ${CFLAGS} ${BIN} ${RLFLAGS} ${LIBFTFLAGS} -o ${NAME} 
	@echo "\r${GREEN}${NAME} successfully created. 📂${DEFAULT}"

.PHONY		:	run
run			:	all
	@echo "${GREEN}Running ${NAME} ... ${DEFAULT}"
	@./${NAME}

.PHONY		:	leaks
leaks		:	debug
	@echo "${RED}LEAKS CHECKER${DEFAULT}"; 
	@valgrind ${VALGFLAGS} ./${NAME}
	

.PHONY		:	libft	
libft		:
	@make -C ${LIBFT_DIR}


.PHONY		:	clean
clean		:
	@${RM} ${BINDIR} 
	@echo "${YELLOW} ${NAME} binary files successfully removed 🗑${DEFAULT}"

.PHONY		:	fclean
fclean		:	clean
	@${RM} ${NAME}
	@echo "${RED} ${NAME} executable successfully removed 🗑${DEFAULT}"

.PHONY		:	lclean
lclean		:
	@${RM} ${LIBDIR}
	@echo "${RED}Libraries successfully removed 🗑${DEFAULT}"

.PHONY		:	re
re: fclean all

.PHONY		:	bonus
bonus		:	all

.PHONY		:	norm
norm		:
	@echo "$(DARKGRAY)Checking norminette output...$(DEFAULT)"
	@if norminette $(INCDIR) $(SRC) $(LIBFT_DIR) | grep -vq "OK!$$"; then \
        echo "$(RED)Not all lines end with 'OK!'$(DEFAULT)"; \
		norminette $(HEADER_DIR) $(SRC) | grep -v "OK!$$"; \
	else \
        echo "$(GREEN)All lines end with 'OK!'$(DEFAULT)"; \
	fi

#--- COLORS ---#

RED					= \033[1;31m

GREEN				= \033[1;32m

BLUE				= \033[1;34m

YELLOW				= \033[1;33m

DARKGRAY			= \033[1;30m

DEFAULT 			= \033[0;30m
