CFILES = pipex.c foundPath.c joinChrNstr.c splitTrim.c substrDup.c

OFILES = ${CFILES:.c=.o}

CBONUS = pipex_bonus.c foundPath_bonus.c joinChrNstr_bonus.c splitTrim_bonus.c substrDup_bonus.c \
	get_next_line_utils.c get_next_line.c here_doc_.c

OBONUS = ${CBONUS:.c=.o}

CC = gcc
W = -Wall -Werror -Wextra
INC = pipex.h
INCB = pipex_bonus.h
NAME = pipex

YELLOW=\033[1;33m
NC=\033[0m
GREEN=\033[0;32m
RED=\033[0;31m

define HEADER
			      ___                     ___         ___           ___      
			     /\  \                   /\  \       /\__\         /|  |     
			    /::\  \     ___         /::\  \     /:/ _/_       |:|  |     
			   /:/\:\__\   /\__\       /:/\:\__\   /:/ /\__\      |:|  |     
			  /:/ /:/  /  /:/__/      /:/ /:/  /  /:/ /:/ _/_   __|:|__|     
			 /:/_/:/  /  /::\  \     /:/_/:/  /  /:/_/:/ /\__\ /::::\__\_____
			 \:\/:/  /   \/\:\  \__  \:\/:/  /   \:\/:/ /:/  / ~~~~\::::/___/
			  \::/__/     ~~\:\/\__\  \::/__/     \::/_/:/  /      |:|~~|    
			   \:\  \        \::/  /   \:\  \      \:\/:/  /       |:|  |    
			    \:\__\       /:/  /     \:\__\      \::/  /        |:|__|    
			     \/__/       \/__/       \/__/       \/__/         |/__/    
			
endef
export HEADER

all : ${NAME}

	@echo " ${RED}$$HEADER${NC} "

${NAME} : ${OFILES}
	@$(CC) $(OFILES) $(W) -o $(NAME)
	@echo "${YELLOW}$(NAME) created ${NC}"

%.o:%.c ${INC}
	@${CC} ${W} -o $@ -c $<
	@echo "${GREEN}$@ created${NC}"

%.o:%.c ${INCB}
	@${CC} ${W} -o $@ -c $<
	@echo "${GREEN}$@ created${NC}"

clean:
	@rm -f *.o

fclean : clean
	@rm -f file2
	@rm -f ${NAME}

re : fclean all

.PHONY: all clean fclean re

bonus: all ${OBONUS} $(INCB)
	@$(CC) $(OBONUS) $(W) -o $(NAME) 