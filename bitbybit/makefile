all: bit.exe

bit.exe: bit.o
	gcc -o bit.exe bit.o
	chmod a+x bit.exe
bit.o: bit.c
	gcc -c bit.c
	

clean:
	rm bit.o bit.exe
	

