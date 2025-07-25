CC ?= wclang
SRCS := CPU.c Display.c main.c FontArrays/Font.c InputHandler.c Poppers.c
OBJS := $(patsubst %.c,%.o,$(SRCS))
OUT := c8emu

LDFRAMEWORKS := -framework Cocoa -framework IOKit \
				-framework CoreVideo -framework CoreFoundation \
				-framework AppKit -framework QuartzCore

LDFLAGS := -L/opt/will/lib -lomp -L/opt/will/lib/other-static -L/opt/will/lib/SDL -lSDL2 -lraylib $(LDFRAMEWORKS)
CFLAGS := -O2
CPPFLAGS := -I/opt/will/include -fopenmp

$(OUT): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c 
	$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f $(OUT) $(OBJS)