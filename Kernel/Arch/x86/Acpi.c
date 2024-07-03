
#include <Common.h>
#include <Arch/x86/Acpi.h>
#include <Screen/Terminal.h>


// See https://github.com/limine-bootloader/limine/blob/v4.x-branch/PROTOCOL.md
static volatile struct limine_rsdp_request rsdpRequest = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0
};


static bool isAcpiXsdt = false;



// Performs checksum of a table
static bool checkTable(const void* table, size_t lenght) {
    uint8_t* tablePtr = (uint8_t*)table;
    uint32_t len = 0;

    for (size_t i = 0; i < lenght; i++) {
        len += tablePtr[i];
    }

    return (len & 0xff) == 0;
}



void acpiInit(void) {
    struct rsdpDescriptor* rsdp = rsdpRequest.response->address;
    uint64_t rootTablePointer = 0;

    // If 0 we are good to go, or else... INTO THE MATRIX
    if (checkTable(rsdp, sizeof(rsdp)) != 0) {
        __asm__ volatile("cli");
        for (;;) {
            __asm__ volatile("hlt");
        }
    }

    if (rsdp->revision > 0) {
        // ACPI 2.0 or higher

        struct rsdp2Descriptor* rsdp2 = (struct rsdp2Descriptor*)rsdp;

        if (rsdp2->xsdtAddress != 0) {
            log("Found XSDT!\n");
            rootTablePointer = rsdp2->xsdtAddress;
            isAcpiXsdt = true;

        } else {
            log("No XSDT, using RSDT.\n");
            rootTablePointer = (uint64_t)rsdp2->rsdtAddress;
        }

    } else if (rsdp->revision == 0) {
        // ACPI 1.0

        log("ACPI 1.0. Using RSDT.\n");
        rootTablePointer = (uint64_t)rsdp->rsdtAddress;
    }

    if (!rootTablePointer) log("%bNo ACPI root table!\n", 0xef233c);
    
}
