CC ?= wclang
OUT = CHIPAS
SRCS = LoadFile.c Main.c Tokenize.c 
OBJS := $(patsubst %.c,%.o,$(SRCS))

$(OUT): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c 
	$(CC) -o $@ -c $<

clean:
	rm -f $(OBJS) $(OUT)