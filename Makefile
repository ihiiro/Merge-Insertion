CFLAGS = -std=c++98 -Wall -Wextra -Werror

CFILES = main.cpp

HEADERS = mi.hpp

NAME = mi

OFILES = $(CFILES:.cpp=.o)

%.o: %.cpp
	c++ $(CFLAGS) -c $<

$(NAME): $(OFILES) $(HEADERS) Makefile mi.tpp
	c++ $(OFILES) -o $@

all: $(NAME)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all