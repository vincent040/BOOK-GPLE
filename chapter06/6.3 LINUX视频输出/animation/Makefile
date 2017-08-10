SRC = $(wildcard *.c)
BIN = $(patsubst %.c, %, $(SRC))

CC = arm-none-linux-gnueabi-gcc

CPPFLAGS = 
LDFLAGS  =

all:$(BIN)

$(BIN):%:%.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

clean:
	$(RM) *.o .*.sw? $(BIN)