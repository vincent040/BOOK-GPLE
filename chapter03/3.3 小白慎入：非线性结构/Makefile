CFLAGS = -I./headers -g
BIN = bst avl

all:$(BIN)

$(BIN):%:%.o drawtree.o queue.o travel.o
	$(CC) -o $@ $^ $(CFLAGS)


queue.o:queue.c
	$(CC) -o $@ $< -c $(CFLAGS)

travel.o:travel.c
	$(CC) -o $@ $< -c $(CFLAGS)

bst.o:bst.c
	$(CC) -o $@ $< -c $(CFLAGS)

avl.o:avl.c
	$(CC) -o drawtree.o drawtree.c -c $(CFLAGS) -DAVL
	$(CC) -o $@ $< -c $(CFLAGS) -DAVL

clean:
	$(RM) *.o $(BIN)

distclean:clean
	$(RM) .*.sw? *html
