CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
NAME = PmergeMe
HEADER = PmergeMe.hpp
SRC = PmergeMe.cpp main.cpp 

all : $(NAME)

$(NAME) : $(SRC) $(HEADER)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

fclean :
	@rm -rf $(NAME)

re : fclean all