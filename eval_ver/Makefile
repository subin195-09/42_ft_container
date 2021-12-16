# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/16 14:36:54 by skim              #+#    #+#              #
#    Updated: 2021/12/16 15:34:19 by skim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++
CFLAGS = -Wall -Werror -Wextra

VECTOR = vTest
STACK = stTest
MAP = mTest
SET = seTest

all : vector_test stack_test map_test

bonus : all set_test

vector_test :
	@$(CC) $(CFLAGS) -std=c++98 vector_test.cpp -o $(VECTOR)

stack_test :
	@$(CC) $(CFLAGS) -std=c++98 stack_test.cpp -o $(STACK)

map_test :
	@$(CC) $(CFLAGS) -std=c++98 map_test.cpp -o $(MAP)

set_test :
	@$(CC) $(CFLAGS) -std=c++98 set_test.cpp -o $(SET)

clean :
	@rm -rf $(VECTOR) $(STACK) $(MAP) $(SET)

fclean : clean

re : fclean all
