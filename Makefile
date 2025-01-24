CC = gcc 
CFLAGS = -Wall 


OBJ = saper.o score.o maze.o
SRC = saper.c score.c maze.c

EXEC = a.out

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)


saper.o: saper.c score.h maze.h
	$(CC) $(CFLAGS) -c saper.c

score.o: score.c score.h
	$(CC) $(CFLAGS) -c score.c

maze.o: maze.c maze.h
	$(CC) $(CFLAGS) -c maze.c

test: $(EXEC)
	@echo "Uruchamiam testy..."
	./$(EXEC) < test_input.txt > output.txt
	@echo "Testy zakończone. Zobacz output.txt, aby sprawdzić wyniki."


clean:
	rm -f $(OBJ) $(EXEC) output.txt

test_output:
	cat output.txt
