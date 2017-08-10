CFLAGS := -O0 -Wall $(ABC)
DEBUG ?= -g
CFLAGS += $(DEBUG)

SRC = ${wildcard *.c}

myls:$(SRC) myls.h
	- $(CC) $(CFLAGS) -o $@ $^

clean:
	- $(RM) -f $(OBJS) .*.sw? *.o myls 

.PHONY:clean all
