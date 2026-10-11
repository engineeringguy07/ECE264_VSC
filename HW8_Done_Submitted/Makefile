CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS)
EXEC = hw8
OBJS = main.o shuffle.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS)
	$(GCC) $(OBJS) -o $(EXEC)

%.o: %.c shuffle.h
	$(GCC) -c $<

test: $(EXEC)
	./$(EXEC) 3 1 | sort > output3_1
	./$(EXEC) 3 2 | sort > output3_2
	./$(EXEC) 4 2 | sort > output4_2
	./$(EXEC) 6 2 | sort > output6_2

testid: test
	diff -w output3_1 expected/expected3_1
	diff -w output3_2 expected/expected3_2
	diff -w output4_2 expected/expected4_2
	diff -w output6_2 expected/expected6_2

memory: $(EXEC)
	$(VALGRIND) --log-file=log3_1 ./$(EXEC) 3 1
	$(VALGRIND) --log-file=log3_2 ./$(EXEC) 3 2
	$(VALGRIND) --log-file=log4_2 ./$(EXEC) 4 2
	$(VALGRIND) --log-file=log6_2 ./$(EXEC) 6 2

clean:
	/bin/rm -f *.o $(EXEC) output?_? log?_?