#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define __NR_zone_stats 343

int main(int argc, char *argv[])
{
	syscall(__NR_zone_stats);
	return 0;
}
