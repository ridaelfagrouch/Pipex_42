CFILES = pipex.c pipex_utils.c

OFILES = ${CFILES:.c=.o}

# CBONUS = 

# OBONUS = ${CBONUS:.c=.o}

CC = gcc
W = -Wall -Werror -Wextra
INC = pipex.h
# INC_B = pipex_bonus.h
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
	@make -C ./pipex_libft
	@$(CC) $(OFILES) $(W) ./pipex_libft/libft.a -o $(NAME)
	@echo "${YELLOW}$(NAME) created ${NC}"

%.o:%.c ${INC}
	@${CC} ${W} -o $@ -c $<
	@echo "${GREEN}$@ created${NC}"

clean:
	@rm -f *.o
	@make clean -C ./pipex_libft

fclean : clean
	@rm -f file2.txt
	@rm -f ${NAME}
	@make fclean -C ./pipex_libft

re : fclean all

.PHONY: all clean fclean re

# bonus: all ${OBONUS} $(INC_B)
# 	@$(CC) $(OBONUS) $(W) ./pipex_libft/libft.a  -o $(NAME)
# 	@echo "$(NAME) created"