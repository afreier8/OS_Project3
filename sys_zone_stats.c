#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/mmzone.h>
#include <asm/pgtable.h>
#include <linux/page-flags.h>

asmlinkage int sys_zone_stats(void){
        struct zone *this_zone;
        int i;
        struct page *cached_page;
        struct zone_lru this_lru;
        int active_pages = 0;
        int inactive_pages = 0;
        int active_ref = 0;
        int inactive_ref = 0;
        for_each_zone(this_zone){
                for_each_lru(i) {
                        this_lru = this_zone->lru[i];
                        list_for_each_entry(cached_page, &this_lru.list, lru) {     
                                if(i == LRU_ACTIVE_ANON || i == LRU_ACTIVE_FILE){
                                        active_pages++;
                                        if(PageReferenced(cached_page)){
                                                active_ref++;
                                        }
                                }else{
                                        inactive_pages++;
                                        if(PageReferenced(cached_page)){
                                                inactive_ref++;
                                        }
                                }
                        }
                }
                
        }
        printk("Total Pages: %d \n",active_pages + inactive_pages);
        printk("Active pages: %d \n Active Referenced: %d \n", active_pages, active_ref);
        printk("Inactive pages: %d \n Inactives Referenced: %d", inactive_pages, inactive_ref);
        return 0;
}
