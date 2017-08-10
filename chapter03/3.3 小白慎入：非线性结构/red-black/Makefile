SRC += ../drawtree.c
SRC += ../travel.c
SRC += ../queue.c

SRC += rb_common.c
SRC += rb_delete.c
SRC += rb_insert.c

CPPFLAGS += -I include/
CPPFLAGS += -DRB

rb:$(SRC) rb_test.c
	$(CC) $^ -o $@ $(CPPFLAGS)

clean:
	$(RM) rb
