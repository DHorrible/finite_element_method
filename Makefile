TARGET = main.out

HDRS = \
	   source/include

SRCS = \
	   source/src/main.c \
	   source/src/element.c \
	   source/src/scheme.c \
	   source/src/result.c \
	   source/src/error.c \
	   source/src/method.c

.PHONY: all main test clean

all: main

main: $(SRCS)
	$(CC) $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) -lm

clean:
	rm -f $(TARGET) $(TST_TARGET)
