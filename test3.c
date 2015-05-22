#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define __NR_vma_props 342

int main(int argc, char argv[])
{
        int pid;
        unsigned long address;

        printf("Enter a process id:\n");
        scanf("%d", &pid);

        printf("Enter a memory address:\n");
        scanf("%ld", &address);

        syscall(__NR_vma_props, address, pid);
        return 0;
}
