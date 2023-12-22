NAME = philo
FLAGS = -Wall -Wextra -Werror -pthread
SOURCES = main.c philosophers1.c philosophers2.c philosophers3.c helper.c threads.c tools.c
OBJECTS = $(SOURCES:.c=.o)


all : $(NAME)

$(NAME) : $(OBJECTS)
	cc $(FLAGS) $(OBJECTS) -g -o $(NAME) 

%.o : %.c
	cc $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f philo
	
re : fclean all
