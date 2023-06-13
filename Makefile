# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 10:27:08 by emlamoth          #+#    #+#              #
#    Updated: 2023/06/13 13:48:02 by fbouchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c			\
		execute.c		\
		arg_list.c		\
		mini_steps.c	\
		parsing.c		\
		quotes.c		\
		dollar_sign.c	\
		meta_chars.c	\
		meta_replace.c	\
		exit.c			\
		make_list_ltkn.c\
		make_list_lcmd.c\
		path.c			\
	
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