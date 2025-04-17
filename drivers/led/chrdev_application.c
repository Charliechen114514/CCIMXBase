#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define ISSUE_BUFFER_N      (40)

static void display_help(const char* app_name)
{
    fprintf(stderr, 
        "do: %s <dev_file> <operations>\n"
        "op: read : read the data from char dev\n"
        "op: write: write the data to char dev:\n"
        "   open: turn on the led\n"
        "   close: turn off the led\n", app_name);
}

int main(int argc, char* argv[])
{
    int check = 0;
    if(argc < 3){
        display_help(argv[0]);
        return -1;
    }

    char* filename = argv[1];

    check = open(filename, O_RDWR);
    if(check < 0){
        fprintf(stderr, "Hey, Error in open filename: %s! with code %d\n", filename, errno);
        return -1;
    }
    
    int result = 0;

    if(!strcmp(argv[2], "read")){
        // process reading issue
        printf("user process the read issue\n");
        char buffer[ISSUE_BUFFER_N];
        result = read(check, buffer, ISSUE_BUFFER_N);
        if(result < 0){
            fprintf(stderr, "Hey, Error in read! filename: %s!\n", filename);
            goto close_issue;   
        }
        printf("user receive from driver: %s\n", buffer);
        // done!
    }else if(!strcmp(argv[2], "write")){
        // process the write
        // printf("args: %d\n", argc);
        if(argc != 4){
            display_help(argv[0]);
            goto close_issue;
        }

        // printf("user process the write issue: %s\n", argv[3]);
        result = write(check, argv[3], strlen(argv[3]));
        if(result < 0){
            fprintf(stderr, "Hey, Error in write! filename: %s!\n", filename);
            goto close_issue; 
        }    
    }else{
        fprintf(stderr, "Unknown options!\n");
        display_help(argv[0]);
        goto close_issue;
    }

close_issue:
    result = close(check);
    if(result < 0){
        fprintf(stderr, "Hey, Error in close device! filename: %s!\n", filename);
        return -1;        
    }        

    return 0;
}