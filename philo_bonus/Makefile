NAME = philo_bonus
FLAGS = -Wall -Wextra -Werror -pthread
SOURCES = main.c philosophers1.c philosophers2.c philosophers3.c helper.c threads.c tools.c check_death.c
OBJECTS = $(SOURCES:.c=.o)


all : $(NAME)

$(NAME) : $(OBJECTS)
	cc $(FLAGS) $(OBJECTS) -o $(NAME) 

%.o : %.c
	cc $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f philo_bonus
	
re : fclean all
