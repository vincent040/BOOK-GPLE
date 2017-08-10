SRC = $(wildcard *.c)
ELF = $(SRC:%.c=%)

CPPFLAGS += -Wall
CPPFLAGS += -DDEBUG

LDFLAGS += -lasound
LDFLAGS += -lpthread
LDFLAGS += -ljpeg
LDFLAGS += -Wl,-rpath=.
LDFLAGS += -Wl,-rpath=./lib

CROSS_COMPILE = arm-none-linux-gnueabi-
CC = $(CROSS_COMPILE)gcc

all:$(ELF)

$(ELF):%:%.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

clean:
	-@$(RM) $(ELF)
