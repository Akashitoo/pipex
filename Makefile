# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalasub <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 19:13:26 by abalasub          #+#    #+#              #
#    Updated: 2024/05/13 01:10:13 by abalasub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror -g
LIBFT = ./libft/libft.a
FT_PRINTF = ./ft_printf/libftprintf.a

SRC = pipex.c \
	init.c \
	utils.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME):$(OBJS)
	$(MAKE) --no-print-directory -C ./libft
	echo "=> 𝙇𝙄𝘽𝙁𝙏 𝙀𝙎𝙏 𝘾𝙊𝙈𝙋𝙄𝙇𝙀́  📚"
	$(MAKE) --no-print-directory -C ./ft_printf
	echo "=> 𝙁𝙏_𝙋𝙍𝙄𝙉𝙏𝙁 𝙀𝙎𝙏 𝘾𝙊𝙈𝙋𝙄𝙇𝙀́  📚"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) -o $(NAME)
	echo "=> 𝙋𝙄𝙋𝙀𝙓 𝙀𝙎𝙏 𝙋𝙍𝙀̂𝙏 !🧪"

clean:
	rm -rf $(OBJS)
	echo "🔴 𝗧𝗢𝗨𝗦 𝗟𝗘𝗦 𝗢𝗕𝗝𝗘𝗧𝗦 𝗢𝗡𝗧 𝗘́𝗧𝗘́ 𝗦𝗨𝗣𝗣𝗥𝗜𝗠𝗘́ 🚮"

fclean:	clean
	rm -rf $(NAME)
	echo "🔴 𝙋𝙄𝙋𝙀𝙓 𝘼 𝙀́𝙏𝙀́ 𝙎𝙐𝙋𝙋𝙍𝙄𝙈𝙀́ 🚮"

re: fclean all

.PHONY: all, clean, fclean, re

.SILENT:
