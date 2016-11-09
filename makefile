FLAGS = -std=c99
MAINFILE = datastructurestest.c
TESTFILES = linkedlist.o stack.o queue.o hashtable.o

datastructurestest: $(TESTFILES) $(MAINFILE)
	gcc $(FLAGS) $(MAINFILE) $(TESTFILES) -o datastructurestest

linkedlist.o: linkedlist.c linkedlist.h
	gcc $(FLAGS) -c linkedlist.c

stack.o: stack.c stack.h
	gcc $(FLAGS) -c stack.c

queue.o: queue.c queue.h
	gcc $(FLAGS) -c queue.c

hashtable.o: hashtable.c hashtable.h
	gcc $(FLAGS) -c hashtable.c

test:
	./datastructurestest
	rm datastructurestest $(TESTFILES)