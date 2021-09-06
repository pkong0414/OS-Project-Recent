# This is a makefile for the logger.

CC = gcc
CFLAGS = -g
TARGET = driver
DEPS = log.h
SRC = driver.c log.c
OBJS = driver.o

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

driver: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	/bin/rm '-f' *.o $(TARGET)


