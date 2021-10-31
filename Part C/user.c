#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

#define TASK_RUNNING			0x0000
#define TASK_INTERRUPTIBLE		0x0001
#define TASK_UNINTERRUPTIBLE		0x0002
#define __TASK_STOPPED			0x0004
#define __TASK_TRACED			0x0008
#define EXIT_DEAD			0x0010
#define EXIT_ZOMBIE			0x0020
#define EXIT_TRACE			(EXIT_ZOMBIE | EXIT_DEAD)
#define TASK_PARKED			0x0040
#define TASK_DEAD			0x0080
#define TASK_WAKEKILL			0x0100
#define TASK_WAKING			0x0200
#define TASK_NOLOAD			0x0400
#define TASK_NEW			0x0800
#define TASK_STATE_MAX			0x1000
#define TASK_KILLABLE			(TASK_WAKEKILL | TASK_UNINTERRUPTIBLE)
#define TASK_STOPPED			(TASK_WAKEKILL | __TASK_STOPPED)
#define TASK_TRACED			(TASK_WAKEKILL | __TASK_TRACED)
#define TASK_IDLE			(TASK_UNINTERRUPTIBLE | TASK_NOLOAD)
#define TASK_NORMAL			(TASK_INTERRUPTIBLE | TASK_UNINTERRUPTIBLE)
#define TASK_REPORT			(TASK_RUNNING | TASK_INTERRUPTIBLE | \
					 TASK_UNINTERRUPTIBLE | __TASK_STOPPED | \
					 __TASK_TRACED | EXIT_DEAD | EXIT_ZOMBIE | \
					 TASK_PARKED)

struct data
{
    int pid;
    int ppid;
    int process;
    int state;
};

#define BUFFER_LENGTH 100000
struct data buffer[BUFFER_LENGTH];

void main()
{
    char *chr = "/dev/process_list";
    int cnt = 0;
    
    int fd = open(chr, O_RDONLY);
    
    if (fd < 0)
    {
        printf("Error %d in file %s opening. fd is %d\n", errno, chr, fd);
    }
    else
    {
        int len = read(fd, buffer, sizeof(buffer));
        char *state;
        while (cnt < len)
        {
            if (buffer[cnt].state == TASK_RUNNING){
                state = "TASK_RUNNING";
            }
            else if (buffer[cnt].state == TASK_INTERRUPTIBLE){
                state = "TASK_INTERRUPTIBLE";
            }
            else if (buffer[cnt].state == TASK_UNINTERRUPTIBLE){
                state = "TASK_UNINTERRUPTIBLE";
            }
            else if (buffer[cnt].state == __TASK_STOPPED){
                state = "__TASK_STOPPED";
            }
            else if (buffer[cnt].state == __TASK_TRACED){
                state = "__TASK_TRACED";
            }
            else if (buffer[cnt].state == EXIT_DEAD){
                state = "EXIT_DEAD";
            }
            else if (buffer[cnt].state == EXIT_ZOMBIE){
                state = "EXIT_ZOMBIE";
            }
            else if (buffer[cnt].state == EXIT_TRACE){
                state = "EXIT_TRACE";
            }
            else if (buffer[cnt].state == TASK_PARKED){
                state = "TASK_PARKED";
            }
            else if (buffer[cnt].state == TASK_DEAD){
                state = "TASK_DEAD";
            }
            else if (buffer[cnt].state == TASK_WAKEKILL){
                state = "TASK_WAKEKILL";
            }
            else if (buffer[cnt].state == TASK_WAKING){
                state = "TASK_WAKING";
            }
            else if (buffer[cnt].state == TASK_NOLOAD){
                state = "TASK_NOLOAD";
            }
            else if (buffer[cnt].state == TASK_NEW){
                state = "TASK_NEW";
            }
            else if (buffer[cnt].state == TASK_STATE_MAX){
                state = "TASK_STATE_MAX";
            }
            else if (buffer[cnt].state == TASK_KILLABLE){
                state = "TASK_KILLABLE";
            }
            else if (buffer[cnt].state == TASK_STOPPED){
                state = "TASK_STOPPED";
            }
            else if (buffer[cnt].state == TASK_TRACED){
                state = "TASK_TRACED";
            }
            else if (buffer[cnt].state == TASK_IDLE){
                state = "TASK_IDLE";
            }
            else if (buffer[cnt].state == TASK_NORMAL){
                state = "TASK_NORMAL";
            }
            else if (buffer[cnt].state == TASK_REPORT){
                state = "TASK_REPORT";
            }
            else
            {
                state = "OTHERS";   
            }
            
            
            printf("PID=%d PPID=%d CPU=%d STATE=%s\n", buffer[cnt].pid, buffer[cnt].ppid, buffer[cnt].process, state);
            
            cnt++;
        }
    }
    close(fd);
}