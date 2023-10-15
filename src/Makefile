CC=g++
FLAG=-std=c++17

main:main.o job.o FCFS.o HRRF.o
	$(CC) $^ -o $@ $(FLAG)

job.o:job.cc
	$(CC) -c $^ -o $@ $(FLAG)

HRRF.o: HRRF.cc
	$(CC) -c $^ -o $@ $(FLAG)

FCFS.o:FCFS.cc
	$(CC) -c $^ -o $@ $(FLAG)

main.o:main.cc
	$(CC) -c $^ -o $@ $(FLAG)

.PHNOY:
clean:
	rm -f main *.o