//log.c implementation file

#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
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
    // Message type as follows: (I/ W/ E/ F). Anything else will result in an error.

    if( (type != 'I') && (type != 'W') && (type != 'E') && (type != 'F')) {
        fprintf(stderr, "log.c: Invalid type. %s\n", strerror(errno));
        return -1;
    }

    //initializing a new node
    log_list *newLog;
    //allocating memory to a new log
    newLog = malloc(sizeof(log_list));

    if(newLog == NULL){
        //return -1 if unsuccessful
        fprintf(stderr, "log.c: ERROR description: %s\n", strerror(errno));
        return -1;
    }
    // getting our total seconds
    time_t epoch_seconds;
    epoch_seconds = time(NULL);

    // calculations will be performed such that we will have time in format of:
    // HH:MM:SS
    // To calculate hours we'll do (epoch_time / 3600) % 24
    // To calculate minutes we'll do (epoch_time / 60) % 60
    // To calculate seconds we'll do (epoch_time % 60)

    // Hours needs to be -5 (we are cst local time and we are converting from UTC)
    newLog->item.hours = ((epoch_seconds / 3600) % 24) - 5;
    newLog->item.minutes = ((epoch_seconds / 60) % 60);
    newLog->item.seconds = (epoch_seconds % 60);
    newLog->item.timestamp = malloc(10*sizeof(char) + 1);

    // converting the newly acquired time units into specified format of: HH:MM:SS for timestamp.
    sprintf( newLog->item.timestamp, "[%02u:%02u:%02u]", newLog->item.hours, newLog->item.minutes, newLog->item.seconds);

    newLog->item.type = type;
    newLog->item.messageLog = malloc(strlen(msg) + 1);
    strcpy(newLog->item.messageLog, msg);

    //printf("log added: %s %c: %s\n", newLog->item.timestamp, newLog->item.type, newLog->item.messageLog);

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
    printf("log.c: memory freed!\n");
}

char *getlog(){
    //The getlog function allocates enough space for a string containing the entire log, copies the log into this string,
    //and returns a pointer to the string. It is the responsibility of the calling program to free this memory when necessary.
    char *entireLog;
    // A successful getlog call returns a pointer to the log string;
    char *logToAdd;
    //pointing at the head of the list
    log_list *nodePtr = head;
    int requiredMem = 0;
    //using memoryCount to keep track of the total amount needed to allocate more memory
    int memoryCount = 0;

    while(nodePtr != NULL){
        requiredMem = strlen(nodePtr->item.timestamp) + sizeof(nodePtr->item.type) + strlen(nodePtr->item.messageLog)+1;
        memoryCount += requiredMem;

        //debugging output
        //printf( "current requiredMem: %d\n", requiredMem);
        //printf( "current memoryCount: %d\n", memoryCount);
        //moving to the next node
        nodePtr = nodePtr->next;
    }
    //after counting memory resetting nodePtr to head
    nodePtr = head;
    if((entireLog = (char*)malloc(memoryCount)) == NULL){
        // it returns a NULL upon unsuccessful invocation.
        printf("log.c: ERROR description: %s\n", strerror(errno));
        return NULL;
    }
    if((logToAdd = (char*)malloc(64))== NULL){
        // it returns a NULL upon unsuccessful invocation.
        printf("log.c: ERROR description: %s\n", strerror(errno));
        return NULL;
    }
    while(nodePtr != NULL){
        //reallocating the appropriate memory for logToAdd.
        requiredMem = strlen(nodePtr->item.timestamp) + sizeof(nodePtr->item.type) + strlen(nodePtr->item.messageLog)+1;
        if((logToAdd = (char*)realloc(logToAdd, requiredMem)) == NULL){
            printf("log.c: ERROR description: %s\n", strerror(errno));
            return NULL;
        }
        sprintf(logToAdd, "%s %c: %s\n", nodePtr->item.timestamp, nodePtr->item.type, nodePtr->item.messageLog);
        strcat(entireLog, logToAdd);
        //moving to the next node
        nodePtr = nodePtr->next;
    }

    //freeing up logToAdd
    free(logToAdd);
    return entireLog;
}

int savelog( char *filename ){
    //The savelog function saves the logged message to a disk file.

    FILE *saveFile;
    char *formattedTime;
    saveFile = fopen(filename, "w");

    if(saveFile == NULL){
        perror("log.c: ERROR");
        //return -1 if unsuccessful
        return -1;
    }
    else {
        //Now writing to file

        // as long as there is a node we will write to file!
        log_list *nodePtr = head;
        while( nodePtr != NULL ){
            fprintf( saveFile, "%s %c: %s\n", nodePtr->item.timestamp, nodePtr->item.type, nodePtr->item.messageLog);
            nodePtr = nodePtr->next;
        }
        //closing file
        if(fclose(saveFile) == -1){
            perror("log.c: ERROR");

            //exiting since file is unable to be closed
            exit(EXIT_FAILURE);
        }
        else {
            printf("File saved to: %s\n", filename);
            //return 0 if successful
            return 0;
        }
    }
}