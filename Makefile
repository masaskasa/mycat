SRC = mycat.c parser.c main.c
EX = mycat
OPT = -Wall -Werror -Wextra

all: mycat

mycat:
	gcc $(SRC) -o $(EX) $(OPT) 

memory_leaks:
	gcc -g -fsanitize=address $(SRC) -o $(EX) $(OPT)

no_flag:
	gcc $(SRC) -o $(EX)

clean:
	rm ./$(EX)

rebuild: clean all