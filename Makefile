all:ex

ex:multi_thread.c
	gcc -std=c99 -pthread -o ex multi_thread.c

run: ex
	./ex test_data.txt 100 3 1

run_valgrind: ex
	run_valgrind --tool=memcheck --leak-check=yes ./ex test_data.txt 100 3 1

clean:
	rm ex