all: scribing

scribing: Scribing.c
	$(CC) -o Scribing Scribing.c -Wall -W -pedantic -std=c99

clean:
	rm scribing