vpath %.c = src1/:src2/
vpath %.h = include/

all:a b

a:a.c head.h
	$(CC) $< -o $@
b:b.c head.h
	$(CC) $< -o $@
