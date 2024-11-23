CC = clang
FLAGS = -O0
SFLAGS = -O3 -S
TARGET = EchoRenderer
SRCS = main.c
HEADERS = vec3.h color.h ray.h

OBJS = $(SRCS:.c=.o)
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC)  -o $@ $^
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run:
	make && ./EchoRenderer > a.ppm && open a.ppm
