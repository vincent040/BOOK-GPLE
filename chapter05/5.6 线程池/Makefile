CC = gcc
CFLAGS = -O0 -Wall -g -lpthread

test:main.c thread_pool.c
	$(CC) $^ -o $@ $(CFLAGS)

debug:main.c thread_pool.c
	$(CC) $^ -o $@ $(CFLAGS) -DDEBUG

clean:
	$(RM) .*.sw? test debug *.o

.PHONY:all clean
