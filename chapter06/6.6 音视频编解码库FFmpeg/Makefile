CROSS_COMPILE = arm-none-linux-gnueabi-
CC = $(CROSS_COMPILE)gcc

LDFLAGS += -lavdevice
LDFLAGS += -lavfilter
LDFLAGS += -lavformat
LDFLAGS += -lavcodec
LDFLAGS += -lswscale
LDFLAGS += -lswresample
LDFLAGS += -lavutil
LDFLAGS += -lrt
LDFLAGS += -lm
LDFLAGS += -lSDL
LDFLAGS += -lz

media_player:media_player.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) 
