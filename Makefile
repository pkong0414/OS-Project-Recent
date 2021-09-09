# This is a makefile for the logger.

CC = gcc
CFLAGS = -g
TARGET = driver
SRC = driver.c log.h
OBJS = driver.o log.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

clean:
	/bin/rm '-f' *.o $(TARGET) *.log


