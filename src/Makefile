CC=g++
FLAG=-std=c++17

main:main.o job.o
	$(CC) main.o job.o -o $@ $(FLAG)

job.o:job.cc
	$(CC) -c $^ -o $@ $(FLAG)

main.o:main.cc
	$(CC) -c $^ -o $@ $(FLAG)

.PHNOY:
clean:
	rm -f main *.o