# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aptive <aptive@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 18:02:37 by aptive            #+#    #+#              #
#    Updated: 2022/03/12 16:58:32 by aptive           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philosophers

# directories
SRCDIR	= ./src
INCDIR	= ./includes
OBJDIR	= ./obj

# src / obj files
SRC		=	main.c \
			philo.c \
			thread.c \
			time.c \

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -D_REENTRANT

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft -l pthread


all :	obj $(FT_LIB) $(NAME)

obj :
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@make -C $(FT)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(FT_LNK) -lm -o $(NAME) -lpthread

clean :
	rm -rf $(OBJDIR)

libclean:	clean
			$(MAKE) clean -C ./libft

fclean :clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re : fclean all
