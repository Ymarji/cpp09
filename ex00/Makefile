CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
NAME = btc
HEADER = BitcoinExchange.hpp
SRC = BitcoinExchange.cpp main.cpp 

all : $(NAME)

$(NAME) : $(SRC) $(HEADER)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

fclean :
	@rm -rf $(NAME)

re : fclean all