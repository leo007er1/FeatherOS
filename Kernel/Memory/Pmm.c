
// *NOTE
// We are using a bitmap allocator design for now, since it's very simple.
// In the future I will implement a better allocator.
// Oh yeah only one page size is supported(0x1000)


#include <Memory/Pmm.h>


static volatile struct limine_memmap_request memmapRequest = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};


// Allocator




// Utils

uint64_t GetMemorySize(void) {
    uint64_t memSize = 0;

    for (uint64_t entry = 0; entry < memmapRequest.response->entry_count; entry++) {
        uint64_t entryType = memmapRequest.response->entries[entry]->type;

        if (entryType != LIMINE_MEMMAP_RESERVED && entryType != LIMINE_MEMMAP_FRAMEBUFFER) {
            memSize += memmapRequest.response->entries[entry]->length;
        }
    }

    return memSize;
}

uint64_t GetUsableMemory(void) {
    uint64_t memSize = 0;

    for (uint64_t entry = 0; entry < memmapRequest.response->entry_count; entry++) {
        uint64_t entryType = memmapRequest.response->entries[entry]->type;

        if (entryType == LIMINE_MEMMAP_USABLE || entryType == LIMINE_MEMMAP_ACPI_RECLAIMABLE \
        || entryType == LIMINE_MEMMAP_ACPI_NVS || entryType == LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
            memSize += memmapRequest.response->entries[entry]->length;
        }
    }

    return memSize;
}