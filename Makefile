# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 10:27:08 by emlamoth          #+#    #+#              #
#    Updated: 2023/07/17 11:01:38 by fbouchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c					\
		execute.c				\
		parsing.c				\
		quotes.c				\
		in_quotes.c				\
		dollar_sign.c			\
		dollar_question.c		\
		meta_chars.c			\
		meta_replace.c			\
		free.c					\
		make_list_ltkn.c		\
		make_list_ltkn_util.c	\
		path.c					\
		path_util.c				\
		builtins.c				\
		env.c					\
		set_meta.c				\
		redirection.c			\
		heredoc.c				\
		export.c				\
		export_utils.c			\
		echo.c					\
		cd.c					\
		exit.c					\
		signal.c				\
		ft_safe_calloc.c		\
		ft_mini_strjoin.c		\
		dshd.c					\
	
LIBRLINE = readline-8.2
LIBRLINE_DIR = ./libs/readline/
RLINE = $(LIBRLINE_DIR)libreadline.a
LIBFT_DIR = ./srcs/libft/
LIBFT = ./srcs/libft/libft.a
SRCS_DIR = ./srcs/
OBJS_DIR = ./srcs/objs_minishell/
OBJS = $(SRCS:$(SCRS_DIR)%.c=$(OBJS_DIR)%.o)

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g -O0
# CFLAGS = -Wall -Wextra -Werror -g -O0 -fsanitize=address
# CFLAGS = -Wall -Wextra -Werror -g -O0 -Wunreachable-code -fsanitize=address


CC = gcc

GREEN = \033[1;32m
RED = \033[1;31m
NC = \033[0;0m

all: readline $(NAME)

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	
$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RLINE) -lncurses -o $(NAME)
	@echo "${GREEN}MINISHELL COMPILED${NC}"

leak: CFLAGS += -g
leak: all
	@reset
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=supp.txt ./$(NAME)

readline :
	@if [ ! -f ./libs/readline/libreadline.a ]; then \
		mkdir -p $(LIBRLINE_DIR); \
		curl -O https://ftp.gnu.org/gnu/readline/$(LIBRLINE).tar.gz; \
		tar -xf $(LIBRLINE).tar.gz; \
		rm -rf $(LIBRLINE).tar.gz; \
		cd $(LIBRLINE) && bash configure && make; \
		mv ./libreadline.a ../libs/readline; \
		rm -rf ../$(LIBRLINE); \
		echo "${GREEN}READLINE INSTALLED${NC}"; \
		fi
		
clean:
	@$(MAKE) clean -C ./srcs/libft
	@rm -rf $(OBJS_DIR)
	@echo "${RED}MINISHELL OBJECTS DELETED${NC}"
	@rm -rf $(LIBRLINE_DIR)
	@echo "${RED}READLINE DELETED${NC}"

fclean: clean
	@$(MAKE) fclean -C ./srcs/libft
	@rm -f $(NAME)
	@echo "${RED}MINISHELL DELETED${NC}"

bonus: all

re: fclean all

.PHONY: all clean fclean bonus re