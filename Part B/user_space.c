#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

#define MAX_STRING_LEN 100

void main()
{
    // close(255);
    char *chr = "/dev/misc_char_dd_banu";
    // char *buffer;
    // char *buffer = (char *)malloc(100, sizeof(char));
    // assert((buffer = malloc(sizeof(char) * MAX_STRING_LEN)) != NULL);

    int fd = open(chr, O_RDONLY);
    if (fd < 0)
    {
        printf("Error %d in file %s opening. fd is %d\n", errno, chr, fd);
    }
    else
    {
        printf("Successful File Access!!\n");
        // int ret = write(fd, "Banu Test", 10);
        // if (ret != 10)
        // {
        //     printf("Error in writing..\n");
        // }
        // else
        // {
        //     printf("Success in writing..\n");
        // }
        char buffer[20];
        // printf("This is just a %s\n",buffer);
        int len = read(fd, buffer, 20);
        printf("Read this content: %s\n", buffer);
    }
    close(fd);
}