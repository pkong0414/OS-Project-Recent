//driver.c

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

int main(int argc, char **argv){

    int opt, timeValue, i;
    char *errFileName= "message.log";
    log dataLog;

    while((opt = getopt(argc, argv, "ht:")) != -1){
        switch(opt){
            case 'h':
                //This is the help parameter. We'll be printing out what this program does and will end the program.
                //If this is entered along with others, we'll ignore the rest of the other parameters to print help
                //and end the program accordingly.
                printf("Usage: %s [-h] [-t sec] [log filename]\n", argv[0]);
                printf("This program is a logging utility that will "
                       "save a message at the end of a list.\n");
                printf("It will also record the time the message was logged.\n");
                printf("-t sets the average interval expected of the logger output.\n");
                exit(EXIT_SUCCESS);
            case 't':
                if(!isdigit(argv[2][0])) {
                    //This case the user uses -t parameter but entered a string instead of an int.
                    printf("value entered: %s\n", argv[2]);
                    fprintf(stderr, "ERROR: -t <seconds>\n");
                    exit(EXIT_FAILURE);
                } else {
                    //-t is entered with an integer so we assign this to our timeValue.
                    timeValue = atoi(optarg);
                    printf("timeValue: %d\n", timeValue);
                    break;
                }
            default: /* '?' */
                printf("ERROR: parameter not recognized.\n");
                fprintf(stderr, "Usage: %s [-h] [-t sec] [log filename]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    //This will make it so that a filename that is entered will be the name of the error log without parameter args.
    printf("optind: %d\n", optind);
    if(argc == 4 || argc == 2) {
        if (!isdigit(argv[optind][0])) {
            errFileName = argv[optind];
            strcat(errFileName,".log");
        } else {
            //This case considers that a person entered a number of some kind or has a number before the letters.
            fprintf(stderr, "Filename must contain a letter of the alphabet first.\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("log fileName: %s\n", errFileName);

    exit(EXIT_SUCCESS);
    return 0;
}