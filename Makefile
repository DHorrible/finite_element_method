TARGET = main.out

# XXX: Don't forget backslash at the end of any line except the last one
# Main
HDRS = \
	   source/include

SRCS = \
	   source/src/main.c \

.PHONY: all main test clean

all: main

main: $(SRCS)
	$(CC) -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) -lm

clean:
	rm -f $(TARGET) $(TST_TARGET)
