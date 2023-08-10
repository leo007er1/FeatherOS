
#include <Arch/x86/ACPI.h>


// See https://github.com/limine-bootloader/limine/blob/v4.x-branch/PROTOCOL.md
static volatile struct limine_rsdp_request rsdpRequest = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0
};



// Performs checksum of a table
static bool checkTable(const void* table, size_t lenght) {
    uint8_t* tablePtr = (uint8_t*)table;
    uint32_t len = 0;

    for (uint16_t i = 0; i < lenght; i++) {
        len += tablePtr[i];
    }

    return (len & 0xff) == 0;
}



void acpiInit(void) {
    struct rsdpDescriptor* rsdp = rsdpRequest.response->address;

    // If 0 we are good to go, or else... INTO THE MATRIX
    if (checkTable(rsdp, sizeof(rsdp)) != 0) {
        __asm__ volatile("cli");
        for (;;) {
            __asm__ volatile("hlt");
        }
    }

    if (rsdp->revision == 0) {
        // ACPI 1.0

        // Parse RSDT
    } else if (rsdp->revision == 2) {
        // ACPI 2.0 and newer

        // Parse XSDT
    }
}
