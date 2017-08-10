SRC = $(wildcard *.c)
BIN = $(patsubst %.c, %, $(SRC))

CC = arm-linux-gcc


CPPFLAGS += -I ./animation
CPPFLAGS += -I /usr/local/jpeg/include

LDFLAGS += -L ./animation
LDFLAGS += -lvani

LDFLAGS += -L /usr/local/jpeg/lib
LDFLAGS += -ljpeg
LDFLAGS += -lpthread


all:$(BIN)


$(BIN):%:%.c
	$(CC) $< -o $@ $(CPPFLAGS) $(LDFLAGS)

libvani.a:$(OBJ)
	$(AR) rcs $@ $(OBJ)
	$(RM) $(OBJ)

$(OBJ):%.o:%.c
	$(CC) $^ -o $@ -c


clean:
	$(RM) $(BIN) .*.sw? *.o 
