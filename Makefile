CC = gcc
CFLAGS = -Wall -g -Iinclude
LDFLAGS = `sdl2-config --cflags --libs` -lm

# final executable
airtracking: main.o render.o window.o
	$(CC) $(CFLAGS) main.o render.o window.o -o airtracking $(LDFLAGS)

# object files
main.o: src/main.c include/render.h include/window.h
	$(CC) $(CFLAGS) -c src/main.c -o main.o

render.o: src/render.c include/render.h
	$(CC) $(CFLAGS) -c src/render.c -o render.o

window.o: src/window.c include/window.h
	$(CC) $(CFLAGS) -c src/window.c -o window.o

clean:
	rm -f *.o airtracking
