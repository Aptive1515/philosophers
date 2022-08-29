# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 18:02:37 by aptive            #+#    #+#              #
#    Updated: 2022/08/29 19:42:05 by tdelauna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

# directories
SRCDIR	= ./src
INCDIR	= ./includes
OBJDIR	= ./obj

# src / obj files
SRC		=	main.c \
			philo_init.c \
			thread.c \
			time.c \
			philo_utils.c\
			action.c\
			ft_utils.c\
			ft_utils_2.c\

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
#-fsanitize=thread -g3
#-D_REENTRANT
#-fsanitize=address

# ft library



all :	obj $(NAME)

obj :
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lm -o $(NAME) -lpthread

clean :
	rm -rf $(OBJDIR)

libclean:	clean


fclean :clean
	rm -rf $(NAME)


re : fclean
	make all
