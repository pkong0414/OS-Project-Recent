//log.h header file

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef LOG_H
#define LOG_H

typedef struct log_struct
{
    time_t time;    // Time stamp
    char type;      // Message type (I/W/E/F)
    char *string;   // Message string
} log;

int addmsg(const char type, const char * msg);
void clearlog();
char *getlog();
int savelog( char * filename );
time_t getTime();

#endif