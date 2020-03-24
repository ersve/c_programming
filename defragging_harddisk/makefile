all: defragging_harddisk.exe

defragging_harddisk.exe: defragging_harddisk.o
	gcc -o defragging_harddisk.exe defragging_harddisk.o
	chmod a+x defragging_harddisk.exe
defragging_harddisk.o: defragging_harddisk.c
	gcc -c defragging_harddisk.c
	

clean:
	rm defragging_harddisk.o defragging_harddisk.exe
