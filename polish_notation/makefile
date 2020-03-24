all: polish.exe

polish.exe: polish.o
	gcc -o polish.exe polish.o
	chmod a+x polish.exe
polish.o: polish.c
	gcc -c polish.c
	

clean:
	rm polish.o polish.exe
	

