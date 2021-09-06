//driver.c

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "log.h"

int main(int argc, char **argv){

    int opt, timeValue;
    char *errFileName= "message";
    char *errExt = ".log";


    while((opt = getopt(argc, argv, "ht:")) != -1){
        switch(opt){
            case 'h':
                printf("Usage: %s [-h] [-t sec] [log filename]\n", argv[0]);
                printf("This program is a logging utility that will "
                       "save a message at the end of a list.\n");
                printf("It will also record the time the message was logged.\n");
                printf("-t sets the average interval expected of the logger output.\n");
                break;
            case 't':
                timeValue = atoi(optarg);
                printf("timeValue: %d\n", timeValue);
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-h] [-t sec] [log filename]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    printf("optind=%d\n", optind);
    errFileName = argv[optind];
    printf("log fileName: %s.log\n", errFileName);


    return 0;
}