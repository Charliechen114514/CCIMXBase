#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "led.h"
#include <sys/ioctl.h>
#define ISSUE_BUFFER_N      (40)

static void display_help(const char* app_name)
{
    fprintf(stderr, 
        "do: %s <dev_file>\n", app_name);
}

int main(int argc, char* argv[])
{
    if(argc < 2){
        display_help(argv[0]);
        return -1;
    }

    char* filename = argv[1];

    int fd = open(filename, O_RDWR);
    if(fd < 0){
        fprintf(stderr, "Hey, Error in open filename: %s! with code %d\n", filename, errno);
        return -1;
    }
    
    int result = 0;
    int cmd, sendee, period_arg;
    while(1)
    {
        printf("Input cmd: ");
        result = scanf("%d", &cmd);
        if(result != 1){
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                ; // 清空输入缓冲区
            }            
        }

        switch(cmd)
        {
            case 1:
                sendee = K_TIMER_STOP;
            break;
            case 2:
                sendee = K_TIMER_START;
            break;
            case 3:
                sendee = K_SET_PERIOD;
                printf("Input period: ");
                result = scanf("%d", &period_arg);
                if(result != 1){
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {
                        ; // 清空输入缓冲区
                    }            
                }               
            break;
        }
        ioctl(fd, sendee, period_arg);
    }
}