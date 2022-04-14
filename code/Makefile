CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O2
LIBS = -lm
OBJS = main.o stack.o operations.o parser.o
TARGET = main

define script = 
	pmccabe *.c | awk -v OFS='\t' 'BEGIN {printf "%s\t%s\t%s\n", "CC", "NOI", "FUNCTION"} {print $1, $3, $6 $7}' | sort -n
endef

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: $(TARGET)
	./main

clean:
	@rm -f $(TARGET) $(OBJS)

test:
	$(value script)

submit:
	cd ..; zip -r submission.zip code/*{.c,.h}
