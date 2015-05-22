#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define __NR_vma_stats 341

int main(int argc, char *argv[])
{
        int pid;
        printf("Enter a process id: \n");
        scanf("%d", &pid);
        syscall(__NR_vma_stats, pid);
        return 0;
}
