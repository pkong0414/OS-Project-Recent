# This is a makefile for the logger.

CC = gcc
CFLAGS = -g
TARGET = driver
SRC = driver.c
OBJS = driver.o

$(TARGET): $(SRC)
	$(CC) $^ -L. -llog -o $(TARGET)

clean:
	/bin/rm '-f' *.o $(TARGET) *.log