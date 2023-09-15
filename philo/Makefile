HEADER = ./inc/philo.h

SRC_DIR 	= ./src/
BUILD_DIR	= ./build

SRCS_NAME =	main.c\
			inits.c\
			frees.c\
			threading.c\
			time_mgmt.c\
			actions.c\
			ft_utils.c\
			printers_debug.c\
			mutexes.c\
			end_checkers.c
		
SRCS	= 	$(addprefix ${SRC_DIR}, ${SRCS_NAME})
OBJS	=	${SRCS:%.c=$(BUILD_DIR)/%.o}

NAME =	philo
CC =	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread
LDFLAGS 	=	-pthread
# fsan		: -g in compile and + -fsanitize=thread in link

$(BUILD_DIR)/%.o: %.c
			@mkdir -p $(dir $@)
			@echo "\033[32m\c"
			${CC} ${CFLAGS} -c $< -o $@
			@echo "\033[0m\c"

all:	${NAME}

${NAME}:	${HEADER} ${OBJS} 
			@echo "\033[32m\c"
			${CC} -o ${NAME} ${OBJS} ${LDFLAGS}
			@echo "Link complete for exec --> \033[4;36;1m${NAME}\033[0m"

clean:
		@rm -rf ${OBJS}
		@echo "\033[32m${NAME} obj cleaned"

fclean:		clean
		@rm -rf ${NAME}
		@echo "\033[32m${NAME} fcleaned"

re:		fclean all

nice:	all clean

.PHONY:	all clean re
