//log.c implementation file

#include "log.h"

int addmsg( const char type, const char * msg ){
    //addmsg will add a message to the log

    //return 0 if successful

    //return -1 if unsuccessful
}

void clearlog(){
    // The clearlog function releases all the storage that has been allocated for the logged message
    // and empties the list of logged messages.
}

char *getlog(){
    //The getlog function allocates enough space for a string containing the entire log, copies the log into this string,
    //and returns a pointer to the string. It is the responsibility of the calling program to free this memory when necessary.

    // A successful getlog call returns a pointer to the log string;

    // it returns a NULL upon unsuccessful invocation.
}

int savelog( char *filename ){
    //The savelog function saves the logged message to a disk file.

    FILE *saveFile;

    saveFile = fopen(filename, "w");

    if(saveFile == NULL){
        //return -1 if unsuccessful
        return -1;
    }
    else {

        //closing file
        fclose(saveFile);

        //return 0 if successful
        return 0;
    }
}

time_t getTime(){
    //This function will use time() to get the seconds and make the necessary conversion for time.
}