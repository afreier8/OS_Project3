#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/fs.h>
#include <asm/page.h>
#include <asm/mman.h>

asmlinkage int sys_vma_stats(int pid)
{
        struct task_struct *this_task;
        struct mm_struct *this_mem;
        struct vm_area_struct *all_vmas;
        struct vm_area_struct this_vma;

        int num_vmas;
        unsigned long prot=0;
        unsigned long start=0;
        int count=0;
        int total_size=0;
        char *name;

        this_task = find_task_by_vpid(pid);
        this_mem = this_task->active_mm;
        all_vmas = this_mem->mmap;
        num_vmas = this_mem->map_count;
        this_vma = *all_vmas;
        start=this_vma.vm_start;

        printk("\nThere are %i virtual memory areas (VMAs).\n", num_vmas);
        for (this_vma = *all_vmas; count < num_vmas; count++)
        {
                printk("-----------------------------\n");
                printk("VMA #%i:\n", count+1);

                printk("-> Start address: 0x%lx\n", this_vma.vm_start);
                printk("-> End address: 0x%lx\n", this_vma.vm_end);
                printk("-> Total size (End - Start): %lu\n", this_vma.vm_end - this_vma.vm_start);

                prot = this_vma.vm_flags;
                printk("-> Access permissions:\n");
                printk("Read permission: %s \n", prot&PROT_READ?"yes":"no"); 
                printk("Write permission: %s \n", prot&PROT_WRITE?"yes":"no"); 
                printk("Execute permission: %s \n", prot&PROT_EXEC?"yes":"no"); 

                if (this_vma.vm_file != NULL) {
                        name = d_path(&this_vma.vm_file->f_path, (char*)__get_free_page(GFP_TEMPORARY), PAGE_SIZE);
                        printk("-> Mapped file: %s\n", name);
                }
                total_size += this_vma.vm_end - this_vma.vm_start;
                if (count != num_vmas-1) { this_vma = *(this_vma.vm_next); }
        }
        printk("\nTotal VMA space size (all VMAs): %i\n", total_size);

        return 1;
}
