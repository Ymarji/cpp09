CC = clang++
FLAGS = -Wall -Wextra -Werror -std=c++98
NAME = RPN
HEADER = RPN.hpp
SRC = RPN.cpp main.cpp 

all : $(NAME)

$(NAME) : $(SRC) $(HEADER)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

fclean :
	@rm -rf $(NAME)

re : fclean all