CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O2
LIBS = -lm
OBJS = main.o stack.o operations.o
TARGET = main
TEST = medidas_software.py
TARGETFOLDER = code

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: $(TARGET)
	./main

clean:
	@rm -f $(TARGET) $(OBJS)

test:
	cd ..; $(TEST) $(TARGETFOLDER)
