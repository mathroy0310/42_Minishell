# **************************************************************************** #
#                                                                              #
#                                                      ██   ██ ██████          #
#    Makefile                                          ██   ██      ██         #
#                                                      ███████  █████          #
#    By: maroy <maroy@student.42.qc>                        ██ ██              #
#                                                           ██ ███████.qc      #
#    Created: 2023/07/27 15:41:11 by maroy                                     #
#    Updated: 2023/07/31 12:30:22 by maroy            >(.)__ <(.)__ =(.)__     #
#                                                      (___/  (___/  (___/     #
# **************************************************************************** #

#--- PROGRAM NAME ---#

NAME		=	minishell

#--- LIBRARIES AND HEADERS ---#

LIBDIR	=	libs
LIBFT	=	${LIBDIR}/libft
MAKELIB	=	${MAKE} -C ${LIBFT}

HEADER_DIR		= inc/
HEADER_SRC		= minishell.h
HEADERS			= $(addprefix $(HEADER_DIR), $(HEADER_SRC))
LIBFT_HEADER	=	${LIBFT}/libft.h

LIBRLINE = readline-8.2
LIBRLINE_DIR = ./libs/readline/
RLINE = $(LIBRLINE_DIR)libreadline.a

#--- COLORS ---#

RED = \033[1;31m

GREEN = \033[1;32m

BLUE = \033[1;34m

YELLOW = \033[1;33m

DARKGRAY= \033[1;30m

DEFAULT = \033[1;30m

#--- COMMAND VARIABLES ---#

CC		=	gcc

CFLAGS 	=	-Wall -Wextra -Werror -std=c17

RLFLAGS	=	-lreadline -lcurses

MK		=	mkdir -p

RM		=	rm -rf

#--- SOURCE, INCLUDE AND BINARIES DIRECTORIES ---#

INCDIR	=	inc

SRCDIR	=	src

SRCS	=	main.c

BINDIR	=	bin

BIN		=	$(addprefix ${BINDIR}/, ${SRCS:.c=.o})

VPATH	=	${SRCDIR}

#--- RULES ---#

${BINDIR}/%.o	: %.c
	@echo "${DARKGRAY}Compiling${WHITE}... $(@F)"
	@${CC} ${CFLAGS} -I${INCDIR} -I${LIBDIR} -I${LIBFT}/inc -c $< -o $@

all				: readline ${NAME}

readline :
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
		echo "${BLUE}Readline successfully created 🗄${WHITE}"; \
		fi

${NAME}			:	${BINDIR} ${BIN} ${HEADERS} ${LIBDIR_HEADER}
	@${MAKELIB}
	@${CC} ${CFLAGS} ${BIN} ${RLLIB} ${RLFLAGS} -o ${NAME} ${LIBFT}/libft.a
	@echo "${GREEN}Minishell successfully created. 📂${WHITE}"

${BINDIR}		:
	@${MK} ${BINDIR}

clean			:
	@${MAKELIB} clean
	@${RM} ${BINDIR}
	@echo "${YELLOW}Minishell binary files successfully removed 🗑${WHITE}"

fclean			:	clean
	@${MAKELIB} fclean
	@${RM} ${NAME}
	@echo "${RED}Minishell executable successfully removed 🗑${WHITE}"

re	 			:	fclean all

bonus			:	all

norm:
	@echo "$(DARKGRAY)norminette! $(DEFAULT)"
	@norminette $(INCDIR) $(SRCDIR) $(LIBFT)/src $(LIBFT)/inc

.PHONY	 		:	all clean fclean re readline norm bonus