#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include <iostream>

typedef int64_t integer;

int main(int argc, const char * argv[]) {
    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;
    integer noob = 2;
    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                        (host_info64_t)&vm_stats, &count))
    {
        long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;

        long long used_memory = ((int64_t)vm_stats.active_count +
                                 (int64_t)vm_stats.inactive_count +
                                 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;


        
        long long free_memory_gb = free_memory / 1e+9;
        long long used_memory_gb = used_memory / 1e+9;
        int64_t total_memory_gb = free_memory_gb + used_memory_gb;
        printf("free memory: %lld\nused memory: %lld\ntotal memory: %lli\n", free_memory_gb, used_memory_gb, total_memory_gb);
        printf("use percentage: %lld", (used_memory_gb / total_memory_gb) * 100);
    }

    return 0;
}