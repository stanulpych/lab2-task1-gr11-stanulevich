CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = program
SRCS = main.c task1.c task2.c task3.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run