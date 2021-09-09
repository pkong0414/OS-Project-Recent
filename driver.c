//driver.c

#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

int main(int argc, char **argv){

    int opt, timeValue, i, randomError, totalLog;
    char *filename= "message.log";
    char *messageLog, *entireLog;
    time_t t;

    timeValue = 1;
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
                    //timeValue cannot have a value of 0. This will prevent that case.
                    if(timeValue <= 0){
                        timeValue = 1;
                    }
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
            filename = argv[optind];
            strcat(filename,".log");
        } else {
            //This case considers that a person entered a number of some kind or has a number before the letters.
            fprintf(stderr, "Filename must contain a letter of the alphabet first.\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("log fileName: %s\n", filename);
    bool logging = true;

    //We need to a report time because this will be in the interval of random ( 0 - 2 * timeValue ).
    int reportTime = 0;

    totalLog = 0;
    int logCount = 0;

    int randMax = (2 * timeValue);

    //initializing RNG
    srand((unsigned)time(&t));

    while(logging){

        //We are getting our report time. This will give us the means to generate an average 0 - timeValue.
        //We'll round down using floor and convert it to int before assigning to reportTime
        reportTime = rand() % randMax;

        printf("reportTime: %d\n", reportTime);
        sleep(reportTime);
        //This will give us the random error log for this program
        randomError = rand() % 4;
        //now we'll handle adding the details to our datalog

        if(randomError == 0){
            messageLog = "Exceeded the number of threads.";
            if(addmsg( 'I', messageLog) == -1){
                perror("driver: Unable to add a new log\n");
            }
            else {
                printf("driver: log added!\n");
            }
        }
        else if(randomError == 1){
            messageLog = "Not enough memory to allocate kernel structures.";
            if(addmsg( 'W', messageLog) == -1){
                perror("driver: Unable to add a new log\n");
            }
            else {
                printf("driver: log added!\n");
            }
        }
        else if(randomError == 2){
            messageLog = "Parameter is invalid.";
            if(addmsg( 'E', messageLog) == -1){
                perror("driver: Unable to add a new log\n");
            }
            else {
                printf("driver: log added!\n");
            }
        }
        else if(randomError == 3){
            messageLog = "Function not supported on this platform.";
            if(addmsg( 'F', messageLog) == -1){
                perror("driver: Unable to add a new log\n");
            }
            else {
                printf("driver: log added!\n");
            }
            //using getLog() before we wipe it clean
            if((entireLog = getlog()) != NULL){
                printf("%s", entireLog);
            }
            else {
                perror("driver: ERROR: unable to get the entire log\n");
            }
            if( savelog(filename) != 0){
                //savelog() returns either a 0 (success) or -1 (unsuccessful)
                perror("save unsuccessful\n");
            }
            else {
                printf("save successful\n");
            }
            clearlog();
            exit(EXIT_SUCCESS);
        }

        totalLog += 1;
        logCount += 1;
        if(totalLog == 10){
            logging = 0;
        }
    }
    //using getLog() before we wipe it clean
    if((entireLog = getlog()) != NULL){
        printf("%s", entireLog);
    }
    else {
        perror("driver: ERROR: unable to get the entire log\n");
    }
    //we will clear the log after finished using the log
    clearlog();
    exit(EXIT_SUCCESS);
    return 0;
}