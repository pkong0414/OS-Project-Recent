# This is a makefile for the logger.

CC = gcc
CFLAGS = -g.
TARGET = driver
DEPS = log.h
SRC = driver.c log.c
OBJ = driver.o

%.o : %.c $(DEPS)
  $(CC) -c -o $@ $< $(CFLAGS)

driver: driver.o
  $(CC) -o driver driver.o

.PHONY: clean
clean:
        rm *.o


