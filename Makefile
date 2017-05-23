# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/07 12:02:38 by amoinier          #+#    #+#              #
#    Updated: 2017/05/23 13:57:23 by amoinier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED =		\033[31m
GRE =		\033[32m
YEL =		\033[33m
BLU =		\033[34m
CYA =		\033[36m
STD =		\033[39m

NAME =		ft_ls

IDIR =		./includes/

SDIR =		./srcs/
SRCS =		$(shell ls srcs/)

ODIR =		./objs/
OBJS =		$(SRCS:.c=.o)
OBCC =		$(addprefix $(ODIR),$(OBJS))

FLAG =		-g -Wall -Wextra -Werror -I$(IDIR) -I./libft/includes/

all: $(NAME)

$(NAME): header $(OBCC)
	@echo "  ${BLU}+ Compilation program:${STD} $@"
	@make -C ./libft/
	@gcc $(FLAG) $(OBCC) -L libft/ -lft -o $(NAME)

$(ODIR)%.o: $(SDIR)%.c
	@echo "  ${GRE}+ Compilation:${STD} $^"
	@gcc $^ $(FLAG) -c -o $@

header:
	@mkdir -p $(ODIR)
	@echo "${YEL}"
	@echo "FT_LS"
	@echo "By: amoinier"
	@echo
	@echo "${STD}"

clean: header
	@echo "  ${RED}- Remove objects${STD}"
	@make -C ./libft/ clean
	@rm -rf $(OBCC)

fclean: clean
	@echo "  ${RED}- Remove $(NAME)${STD}"
	@make -C ./libft/ fclean
	@rm -f $(NAME)

.PHONY: all $(NAME) $(ODIR)%.o header norme clean fclean re

re: fclean all
