# Philosophers
The dining philosophers problem (concurrency problem) in 42school style. But here the philosophers have to eat, sleep and think in a certain time, otherwise they die.  
The philosophers print to the screen what they are doing at the moment.   
The detailed project description is in the pdf file.  

## Usage
This project was written for and compiled on a Mac.  
```
make
```  
Call ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] in ms.  
```
 ./philo 10 2000 100 100 100
```

## Caveats
This project was a 42School project, we had to program according to a strict norm, for instance using only while loops, having only 25 lines per function, not using inline comments etc.
