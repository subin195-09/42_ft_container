CC = clang++
CFLAGS = -Wall -Werror -Wextra

VECTOR = vector_test
STACK = stack_test
MAP = map_test
SET = set_test

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