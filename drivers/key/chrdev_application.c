#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "key.h"
#define ISSUE_BUFFER_N      (40)

static void display_help(const char* app_name)
{
    printf("usage: %s <dev_file_path>\r\n", app_name);
}

int main(int argc, char* argv[])
{
    if(argc < 2){
        display_help(argv[0]);
        return 1;
    }

    int fd = fd = open(argv[1], O_RDONLY);
    if(fd < 0){
        printf("Failed to open device file: %d", errno);
        return errno;
    }
    int value = 0;
    while(1){
        read(fd, &value, sizeof(value)); 
        if(value == KEY_PRESSED){
            printf("Key is pressed!\n");
        }
    }

    int res = close(fd);
    if(res < 0){ 
        printf("failed to close file\n");
    }
}