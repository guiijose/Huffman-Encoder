CC = gcc


encode: main.c
	$(CC) main.c -o encode

clean:
	rm encode
