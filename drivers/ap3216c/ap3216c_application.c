#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "ap3216c.h"

int main(int argc, char const *argv[])
{
    if(argc != 2){
        printf("usage with dev file!\n");
        return -1;
    }
    
    int fd = open(argv[1], O_RDONLY);
    if(fd < 0){
        printf("failed to open the dev file: %d", errno);
        return -1;
    }
    AP3216CData data;
    while(1)
    {
        int result = read(fd, &data, sizeof(data));
        printf("get the res, ir: %d, als:%d, ps:%d\n", data.ir, data.als, data.ps);
        sleep(1);
    }

    close(fd);
    return 0;
}



