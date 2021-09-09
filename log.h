//log.h header file

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef LOG_H
#define LOG_H

typedef struct log_struct
{
    //time isn't cutting it, especially if I want hh:mm:ss, gonna have to try something else instead
    int hours;
    int minutes;
    int seconds;
    char *timestamp;    // Timestamp
    char type;          // Message type (I/W/E/F)
    char *messageLog;   // Message string
} log_data;

int addmsg( char type, const char * msg);
void clearlog();
char *getlog();
int savelog( char * filename );

#endif