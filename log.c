//log.c implementation file

#include <errno.h>
#include <string.h>
#include "log.h"

typedef struct list_struct {
    log_data item;
    struct list_struct *next;
} log_list;

static log_list *head = NULL;
static log_list *tail = NULL;

int addmsg( char type, const char * msg ){
    // addmsg will add a message to the log

    // Since we are using this program in random for our cases
    // Message type as follows: ( 0:I/ 1:W/ 2:E/ 3:F )
    printf("%c\n", type);
    printf("%s\n", msg);

    log_list *newLog;
    //allocating memory to a new log
    newLog = malloc(sizeof(log_list));

    // getting our seconds
    time_t epoch_seconds;
    epoch_seconds = time(NULL);
    printf( "%ld\n", epoch_seconds);
    newLog->item.time = epoch_seconds;
    newLog->item.type = type;
    newLog->item.messageLog = malloc(strlen(msg) + 1);
    strcpy(newLog->item.messageLog, msg);

    printf("%c: %s\n", newLog->item.type, newLog->item.messageLog);

    if(head == NULL){
        //attaching head to new node as usual
        head = newLog;
        //attaching the tail also to the new node since it is the end node for now
        tail = newLog;
    }
    else {
        //using the end node to attach to the new node
        tail->next = newLog;
        //now new node is attached, tail will point to the new end of the list.
        tail = newLog;
    }
    //return 0 if successful
    return 0;

    //return -1 if unsuccessful
}

void clearlog(){
    // The clearlog function releases all the storage that has been allocated for the logged messages
    // and empties the list of logged messages.

    while( head != NULL ){
        //we'll keep removing things while there's still a head of the list.
        log_list *ptr = head->next;
        free(head);
        head = ptr;
    }
    printf("log cleared!\n");
}

char *getlog(){
    //The getlog function allocates enough space for a string containing the entire log, copies the log into this string,
    //and returns a pointer to the string. It is the responsibility of the calling program to free this memory when necessary.
    char *entireLog;
    // A successful getlog call returns a pointer to the log string;


    return entireLog;
    // it returns a NULL upon unsuccessful invocation.
    return NULL;
}

int savelog( char *filename ){
    //The savelog function saves the logged message to a disk file.

    FILE *saveFile;

    saveFile = fopen(filename, "w");

    if(saveFile == NULL){

        perror("driver: ERROR: Cannot open file.\n");
        //return -1 if unsuccessful
        return -1;
    }
    else {
        //Now writing to file

        // calculations will be performed such that we will have time in format of:
        // HH:MM:SS
        // To calculate hours we'll do (epoch_time / 3600) % 24
        // To calculate minutes we'll do (epoch_time / 60) % 60
        // To calculate seconds we'll do (epoch_time % 60)


        //closing file
        if(fclose(saveFile) == -1){
            perror("driver: ERROR: Failed to close file.\n");
            return -1;
        }
        else {
            //return 0 if successful
            return 0;
        }
    }
}