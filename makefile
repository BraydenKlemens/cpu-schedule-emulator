all: dispatcher

dispatcher:
	gcc -Wall -g -std=c99 -Iinclude src/idispatcher.c -o bin/dispatcher

run:
	./bin/dispatcher < test_inputs/test0.in

vg:
	valgrind ./bin/dispatcher < test_inputs/test0.in

clean:
	rm bin/dispatcher