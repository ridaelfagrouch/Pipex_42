CFILES = pipex.c

OFILES = ${CFILES:.c=.o}

# CBONUS = 

# OBONUS = ${CBONUS:.c=.o}

CC = gcc
W = -Wall -Werror -Wextra
INC = pipex.h
# INC_B = pipex_bonus.h
NAME = pipex

all : ${NAME}

${NAME} : ${OFILES} 
	@make -C ./pipex_libft
	@$(CC) $(OFILES) $(W) ./pipex_libft/libft.a -o $(NAME)
	@echo "$(NAME) created"

%.o:%.c ${INC}
	@${CC} ${W} -o $@ -c $<
	@echo "$@ created"

clean:
	@rm -f *.o
	@make clean -C ./pipex_libft

fclean : clean
	@rm -f ${NAME}
	@make fclean -C ./pipex_libft

re : fclean all

.PHONY: all clean fclean re

# bonus: all ${OBONUS} $(INC_B)
# 	@$(CC) $(OBONUS) $(W) ./pipex_libft/libft.a  -o $(NAME)
# 	@echo "$(NAME) created"