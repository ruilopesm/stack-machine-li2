CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O2
LIBS = -lm
OBJS = main.o stack.o operations.o mathematics.o conversions.o strings.o arrays.o blocks.o parser.o
TARGET = main
DOC_FILE = Doxygen.config
COVERAGE_FILE = Coverage.info

define test_script = 
	pmccabe *.c | awk -v OFS='\t' 'BEGIN {printf "%s\t%s\t%s\n", "CC", "NOI", "FUNCTION"} {print $1, $3, $6 $7}' | sort -n
endef

define coverage_script =
	python3 -m coverxygen --xml-dir ../doc/xml/ --src-dir . --format summary --output Coverage.info
endef

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: $(TARGET)
	./main

clean:
	@rm -f $(TARGET) $(OBJS)

test:
	$(value test_script)

submit:
	cd ..; zip -r submission.zip . -i code/*{.c,.h}

doc: $(DOC_FILE)
	doxygen Doxygen.config

coverage: doc
	$(value coverage_script); clear; cat $(COVERAGE_FILE)

log: 
	chmod +x repl; ./repl
