CFILES = ./mandatory/pipex.c ./mandatory/foundPath.c ./mandatory/joinChrNstr.c ./mandatory/splitTrim.c ./mandatory/substrDup.c

OFILES = ${CFILES:.c=.o}

CBONUS = ./bonus/pipex_bonus.c ./bonus/foundPath_bonus.c ./bonus/joinChrNstr_bonus.c ./bonus/splitTrim_bonus.c ./bonus/substrDup_bonus.c \
	./bonus/get_next_line_utils.c ./bonus/get_next_line.c ./bonus/here_doc_.c

OBONUS = ${CBONUS:.c=.o}

CC = gcc
W = -Wall -Werror -Wextra
INC = ./mandatory/pipex.h
INCB = ./bonus/pipex_bonus.h
NAME = pipex

YELLOW=\033[1;33m
NC=\033[0m
GREEN=\033[0;32m
RED=\033[0;31m

define HEADER_M
						   _ __     _      _ __                  
						  | '_ \   (_)    | '_ \   ___    __ __  
						  | .__/   | |    | .__/  / -_)   \ \ /  
						  |_|__   _|_|_   |_|__   \___|   /_\_\  
						_|"""""|_|"""""|_|"""""|_|"""""|_|"""""| 
						"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-' 

endef
export HEADER_M

define HEADER_B
				   _ __     _      _ __                            _                                      
				  | '_ \   (_)    | '_ \   ___    __ __     o O O | |__     ___    _ _     _  _     ___   
				  | .__/   | |    | .__/  / -_)   \ \ /    o      | '_ \   / _ \  | ' \   | +| |   (_-<   
				  |_|__   _|_|_   |_|__   \___|   /_\_\   TS__[O] |_.__/   \___/  |_||_|   \_,_|   /__/_  
				_|"""""|_|"""""|_|"""""|_|"""""|_|"""""| {======|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""| 
				"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'./o--000'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-' 

endef
export HEADER_B

.PHONY: all clean fclean re print_header_m print_header_b

all : ${NAME}

${NAME} : print_header_m ${OFILES}
	@$(CC) $(OFILES) $(W) -o $(NAME)
	@echo "${YELLOW}$(NAME) created ${NC}"

print_header_m:
	@echo " ${RED}$$HEADER_M${NC} "

print_header_b:
	@echo " ${RED}$$HEADER_B${NC} "

%.o:%.c ${INC}
	@${CC} ${W} -o $@ -c $<
	@echo "${GREEN}$@ created${NC}"

%.o:%.c ${INCB}
	@${CC} ${W} -o $@ -c $<
	@echo "${GREEN}$@ created${NC}"

clean:
	@rm -f ./mandatory/*.o
	@rm -f ./bonus/*.o

fclean : clean
	@rm -f .temp
	@rm -f file2
	@rm -f ${NAME}

re : fclean all

bonus: print_header_b  ${OBONUS} $(INCB)
	@$(CC) $(OBONUS) $(W) -o $(NAME)
	@echo "${YELLOW}$(NAME) created ${NC}"