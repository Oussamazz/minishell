# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 20:13:16 by oelazzou          #+#    #+#              #
#    Updated: 2020/01/15 15:56:52 by oelazzou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_PATH = libft/
INC = -I ./includes/ -I $(LIBFT_PATH)
SRC_DIR = ./src/
OBJ_DIR = ./obj/
FLAGS = -Wall -Wextra -Werror

SRC_NAME = 	builtins.c \
			builtins2.c \
			cd_utils.c \
			clear_screen.c \
			env.c \
			error.c \
			execute.c \
			exec.c \
			ft_putstr_color.c \
			is_exist.c \
			main.c \
			msh_loop.c \
			msh_read_line.c \
			msh_split_line.c \
			node.c \
			printing.c \
			split_commands.c \
			split_quotes.c \
			utils.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(SRCS)
	@make -s -C $(LIBFT_PATH)
	@echo "\033[92m--> libft.a CREATED! <--"
	@gcc $(FLAGS) $(OBJS) $(INC) -L $(LIBFT_PATH) -lft -o $(NAME)
	@echo "\033[1m\033[35m--> minishell CREATED! <--\033[0m"
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj
	@gcc -c $(INC) $^ -o $@
	@echo "\033[92m--> Object file Created <--"
clean:
	@echo "\033[1m\033[93m-> cleaning...\033[0m"
	@make clean -s -C $(LIBFT_PATH)
	@rm -rf $(OBJ_DIR)
	@echo "\033[92m-> libft object files REMOVED!\033[0m"
fclean: clean
	@make fclean -s -C $(LIBFT_PATH)
	@echo "\033[92m-> minishell executable REMOVED!\033[0m"
	@rm -f $(NAME)
	@echo "\033[1m\033[31m---> Done! <----\033[0m"
re: fclean all
