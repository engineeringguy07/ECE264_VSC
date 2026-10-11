CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTS = -DTEST_DIVIDE -DTEST_INTERLEAVE -DTEST_SHUFFLE
GCC = gcc $(CFLAGS) $(TESTS)
EXEC = hw7
OBJS = main.o shuffle.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS)
	$(GCC) $(OBJS) -o $(EXEC)

%.o: %.c shuffle.h
	$(GCC) -c $<

test: $(EXEC)
	./$(EXEC) 4 | sort > output4
	./$(EXEC) 8 | sort > output8
	./$(EXEC) 11 | sort > output11

testid: test
	diff -w output4 expected/expected4
	diff -w output8 expected/expected8
	diff -w output11 expected/expected11

memory: $(EXEC)
	$(VALGRIND) --log-file=log4 ./$(EXEC) 4
	$(VALGRIND) --log-file=log8 ./$(EXEC) 8
	$(VALGRIND) --log-file=log11 ./$(EXEC) 11

clean:
	/bin/rm -f *.o $(EXEC) output4 output8 output11 log4 log8 log11