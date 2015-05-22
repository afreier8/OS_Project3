#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <linux/kernel.h>

#define __NR_vma_stats 341

pthread_mutex_t    mutex_lock;


void * sub_thread( void *arg){
    pthread_mutex_lock(&mutex_lock);
    syscall(__NR_vma_stats, getpid());
    pthread_mutex_unlock(&mutex_lock);
}



int main(int argc, char *argv[]){

    int i;
    int num_threads = 2;

    pthread_mutex_init(&mutex_lock, NULL);

    pthread_t thread_mem[num_threads];

    
    for( i = 0; i < num_threads; i++ ){
        pthread_create(&(thread_mem[i]), NULL, (void *) sub_thread, NULL); 
    }

    for( i = 0; i < num_threads; i++ ){
        if(thread_mem[i] != 0) {
            pthread_join(thread_mem[i],NULL);
        }
    }
        return 0;
}