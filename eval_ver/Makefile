# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/16 14:36:54 by skim              #+#    #+#              #
#    Updated: 2021/12/21 15:39:57 by skim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++
CFLAGS = -Wall -Werror -Wextra

VECTOR = vector_test
STACK = stack_test
MAP = map_test
SET = set_test
FT_NAMESPACE = ft
STD_NAMESPACE = std
TARGET = vector_test


all : vector_test stack_test map_test set_test

bonus : all set

vector_test :
	@mkdir -p logs
	@$(CC) $(CFLAGS) -std=c++98 vector_test.cpp -o $(VECTOR) -DTESTED_FT_NAMESPACE=$(STD_NAMESPACE)
	@./$(VECTOR) > logs/$(STD_NAMESPACE)_$(VECTOR).log
	@$(CC) $(CFLAGS) -std=c++98 vector_test.cpp -o$(VECTOR) -DTESTED_FT_NAMESPACE=$(FT_NAMESPACE)
	@./$(VECTOR) > logs/$(FT_NAMESPACE)_$(VECTOR).log

stack_test :
	@mkdir -p logs
	@$(CC) $(CFLAGS) -std=c++98 stack_test.cpp -o $(STACK) -DTESTED_FT_NAMESPACE=$(STD_NAMESPACE)
	@./$(STACK) > logs/$(STD_NAMESPACE)_$(STACK).log
	@$(CC) $(CFLAGS) -std=c++98 stack_test.cpp -o $(STACK) -DTESTED_FT_NAMESPACE=$(FT_NAMESPACE)
	@./$(STACK) > logs/$(FT_NAMESPACE)_$(STACK).log

map_test :
	@mkdir -p logs
	@$(CC) $(CFLAGS) -std=c++98 map_test.cpp -o $(MAP) -DTESTED_FT_NAMESPACE=$(STD_NAMESPACE)
	@./$(MAP) > logs/$(STD_NAMESPACE)_$(MAP).log
	@$(CC) $(CFLAGS) -std=c++98 map_test.cpp -o $(MAP) -DTESTED_FT_NAMESPACE=$(FT_NAMESPACE)
	@./$(MAP) > logs/$(FT_NAMESPACE)_$(MAP).log

set_test :
	@mkdir -p logs
	@$(CC) $(CFLAGS) -std=c++98 set_test.cpp -o $(SET) -DTESTED_FT_NAMESPACE=$(STD_NAMESPACE)
	@./$(SET) > logs/$(STD_NAMESPACE)_$(SET).log
	@$(CC) $(CFLAGS) -std=c++98 set_test.cpp -o $(SET) -DTESTED_FT_NAMESPACE=$(FT_NAMESPACE)
	@./$(SET) > logs/$(FT_NAMESPACE)_$(SET).log

diff :
	@diff logs/$(FT_NAMESPACE)_$(VECTOR).log logs/$(STD_NAMESPACE)_$(VECTOR).log
	@diff logs/$(FT_NAMESPACE)_$(STACK).log logs/$(STD_NAMESPACE)_$(STACK).log
	@diff logs/$(FT_NAMESPACE)_$(MAP).log logs/$(STD_NAMESPACE)_$(MAP).log
	@diff logs/$(FT_NAMESPACE)_$(SET).log logs/$(STD_NAMESPACE)_$(SET).log

time :
	@make time_unit TARGET=$(VECTOR)
	@make time_unit TARGET=$(STACK)
	@make time_unit TARGET=$(MAP)
	@make time_unit TARGET=$(SET)

time_unit :
	@mkdir -p logs
	@printf "\n=====\t$(TARGET)\t====="
	@printf "\ntime 'FT'"
	@$(CC) $(CFLAGS) -std=c++98 $(TARGET).cpp -o$(TARGET) -DTESTED_FT_NAMESPACE=$(FT_NAMESPACE)
	@time ./$(TARGET) > ./logs/$(FT_NAMESPACE)_$(TARGET).log
	@printf "time 'STD'"
	@$(CC) $(CFLAGS) -std=c++98 $(TARGET).cpp -o$(TARGET) -DTESTED_FT_NAMESPACE=$(STD_NAMESPACE)
	@time ./$(TARGET) > ./logs/$(STD_NAMESPACE)_$(TARGET).log

mil_test :
	@cd ./containers_test && ./do.sh

clean :
	@rm -d -rf logs
	@rm -rf $(VECTOR)
	@rm -rf $(STACK)
	@rm -rf $(MAP)
	@rm -rf $(SET)

fclean : clean

re : fclean all
