CFLAGS = -Wall

SRC = $(wildcard *.c)
BIN = $(patsubst %.c, %, $(SRC))

all:$(BIN)

$(BIN):%:%.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	$(RM) $(BIN) *.o .*.sw?
