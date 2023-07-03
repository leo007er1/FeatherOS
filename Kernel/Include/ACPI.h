#pragma once

#include <Common.h>
#include <limine.h>

// RSDP descriptor for ACPI 1.0
struct rsdpDescriptor {
    char signature[8]; // Must contain "RSDP PTR", note that it is not null terminated
    uint8_t checksum;
    char oemId[6];
    uint8_t revision; // If 0 ACPI 1.0, for other versions it's 1
    uint32_t rsdtAddress;
} __attribute__((packed));


// RSDP descriptor for newer ACPI version
struct rsdp2Descriptor {
    char signature[8]; // Same as the other descriptor
    uint8_t checksum;
    char oemId[6];
    uint8_t revision;
    uint32_t rsdtAddress;

    // New fields
    uint32_t lenght;
    uint64_t xsdtAddress;
    uint8_t extendedChecksum;
    uint8_t reserved[3];
} __attribute__((packed));


// Header of all the SDTs
struct acpiSdtHeader {
    char signature[4];
    uint32_t lenght;
    uint8_t revision;
    uint8_t checksum;
    char oemId[6];
    char oemTableId[8];
    uint32_t oemRevision;
    uint32_t creatorId;
    uint32_t creatorRevision;

} __attribute__((packed));


// struct rsdtDescriptor {
//     struct acpiSdtHeader header;
//     uint32_t sdtAddresses[(header.lenght - sizeof(header)) / 4];

// } __attribute__((packed));


// // XSDT is unique to newer ACPI versions
// struct xsdtDescriptor {
//     struct acpiSdtHeader header;
//     uint64_t sdtAddresses[(header.lenght - sizeof(header)) / 8];

// } __attribute__((packed));


void acpiInit(void);