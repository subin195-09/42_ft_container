# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/16 14:36:54 by skim              #+#    #+#              #
#    Updated: 2021/12/18 01:44:41 by skim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++
CFLAGS = -Wall -Werror -Wextra

VECTOR = vTest
STACK = stTest
MAP = mTest
SET = seTest
FT_NAMESPACE = ft
STD_NAMESPACE = std

all : vector stack map

bonus : all set

vector_test :
	@mkdir -p logs
	@$(CC) $(CFLAGS) -std=c++98 vector_test.cpp -o $(FT_NAMESPACE)_$(VECTOR) -DTESTED_FT_NAMESPACE=$(FT_NAMESPACE)
	@./$(FT_NAMESPACE)_$(VECTOR) > logs/$(FT_NAMESPACE)_$(VECTOR).log
	@$(CC) $(CFLAGS) -std=c++98 vector_test.cpp -o $(STD_NAMESPACE)_$(VECTOR) -DTESTED_FT_NAMESPACE=$(STD_NAMESPACE)
	@./$(STD_NAMESPACE)_$(VECTOR) > logs/$(STD_NAMESPACE)_$(VECTOR).log
	@diff logs/$(FT_NAMESPACE)_$(VECTOR).log logs/$(FT_NAMESPACE)_$(VECTOR).log

stack_test :
	@mkdir -p logs
	@$(CC) $(CFLAGS) -std=c++98 stack_test.cpp -o $(FT_NAMESPACE)_$(STACK) -DTESTED_FT_NAMESPACE=$(FT_NAMESPACE)
	@./$(FT_NAMESPACE)_$(STACK) > logs/$(FT_NAMESPACE)_$(STACK).log
	@$(CC) $(CFLAGS) -std=c++98 stack_test.cpp -o $(STD_NAMESPACE)_$(STACK) -DTESTED_FT_NAMESPACE=$(STD_NAMESPACE)
	@./$(STD_NAMESPACE)_$(STACK) > logs/$(STD_NAMESPACE)_$(STACK).log
	@diff logs/$(FT_NAMESPACE)_$(STACK).log logs/$(FT_NAMESPACE)_$(STACK).log

map_test :
	@mkdir -p logs
	@$(CC) $(CFLAGS) -std=c++98 map_test.cpp -o $(FT_NAMESPACE)_$(MAP) -DTESTED_FT_NAMESPACE=$(FT_NAMESPACE)
	@./$(FT_NAMESPACE)_$(MAP) > logs/$(FT_NAMESPACE)_$(MAP).log
	@$(CC) $(CFLAGS) -std=c++98 map_test.cpp -o $(STD_NAMESPACE)_$(MAP) -DTESTED_FT_NAMESPACE=$(STD_NAMESPACE)
	@./$(STD_NAMESPACE)_$(MAP) > logs/$(STD_NAMESPACE)_$(MAP).log
	@diff logs/$(FT_NAMESPACE)_$(MAP).log logs/$(FT_NAMESPACE)_$(MAP).log

set_test :
	@mkdir -p logs
	@$(CC) $(CFLAGS) -std=c++98 set_test.cpp -o $(FT_NAMESPACE)_$(SET) -DTESTED_FT_NAMESPACE=$(FT_NAMESPACE)
	@./$(FT_NAMESPACE)_$(SET) > logs/$(FT_NAMESPACE)_$(SET).log
	@$(CC) $(CFLAGS) -std=c++98 set_test.cpp -o $(STD_NAMESPACE)_$(SET) -DTESTED_FT_NAMESPACE=$(STD_NAMESPACE)
	@./$(STD_NAMESPACE)_$(SET) > logs/$(STD_NAMESPACE)_$(SET).log
	@diff logs/$(FT_NAMESPACE)_$(SET).log logs/$(FT_NAMESPACE)_$(SET).log

clean :
	@rm -d -rf logs
	@rm -rf $(FT_NAMESPACE)_$(VECTOR) $(STD_NAMESPACE)_$(VECTOR)
	@rm -rf $(FT_NAMESPACE)_$(STACK) $(STD_NAMESPACE)_$(STACK)
	@rm -rf $(FT_NAMESPACE)_$(MAP) $(STD_NAMESPACE)_$(MAP)
	@rm -rf $(FT_NAMESPACE)_$(SET) $(STD_NAMESPACE)_$(SET)

fclean : clean

re : fclean all
