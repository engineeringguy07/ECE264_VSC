# You MUST modify this file
CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
# Enable verbose debug prints in hw4.c (guarded by #ifdef DEBUG)
# Usage: make DEBUG=1 <target>
DEBUG ?= 0
ifeq ($(DEBUG),1)
  CFLAGS += -DDEBUG
endif
GCC = gcc $(CFLAGS)
EXEC = hw4
OBJS = hw4.o integrator-hw4.o func1.o func2.o func3.o func4.o func5.o

all: $(EXEC)

# Build main executable linking all object files
$(EXEC): $(OBJS)
	$(GCC) $(OBJS) -o $(EXEC) -lm

# Build hw4.o
hw4.o: hw4.c hw4.h
	$(GCC) -c hw4.c -o hw4.o

# Build integrator-hw4.o with TEST_INTEGRATE and RUN_INTEGRATE macros enabled
integrator-hw4.o: integrator-hw4.c hw4.h
	$(GCC) -c -DTEST_INTEGRATE -DRUN_INTEGRATE integrator-hw4.c -o integrator-hw4.o

# Compile func1
func1.o: func1.c
	$(GCC) -c func1.c

# Compile func2
func2.o: func2.c
	$(GCC) -c func2.c

# Compile func3
func3.o: func3.c
	$(GCC) -c func3.c

# Compile func4
func4.o: func4.c
	$(GCC) -c func4.c

# Compile func5
func5.o: func5.c
	$(GCC) -c func5.c

# Test integrate using provided test cases
testall: $(EXEC)
	mkdir -p outputs
	echo "testing hw4"
	./$(EXEC) testcases/test1 > outputs/output1.out
	./$(EXEC) testcases/test2 > outputs/output2.out
	./$(EXEC) testcases/test3 > outputs/output3.out
	./$(EXEC) testcases/test4 > outputs/output4.out

clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov hw4.prof
	/bin/rm -f $(EXEC)
	/bin/rm -rf outputs