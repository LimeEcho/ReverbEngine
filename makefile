CC = clang
FLAGS = -O0 -g
SFLAGS = -O3 -S
TARGET = build/reverb
SRCS = main.c color.c camera.c vec3.c hittable.c sphere.c ray.c material.c
HEADERS = $(wildcard *.h)
OBJS = $(patsubst %.c, build/%.o, $(SRCS))

.PHONY: all clean run debug

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -g -o $@ $^

build/%.o: %.c $(HEADERS)
	mkdir -p build
	$(CC) $(FLAGS) -c $< -o $@

build/%.s: %.c $(HEADERS)
	mkdir -p build
	$(CC) $(SFLAGS) -o $@ $<

clean:
	rm -rf $(OBJS) $(TARGET) renderOut.ppm ./build/*.dSYM

run:
	make && ./build/reverb && open renderOut.ppm

debug: $(TARGET)
	dsymutil build/reverb -o build/reverb.dSYM
	lldb -o "file $(TARGET)" -o "target symbols add build/reverb.dSYM/Contents/Resources/DWARF/reverb"
