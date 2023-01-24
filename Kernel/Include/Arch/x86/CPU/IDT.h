

#ifndef IdtHeader
#define IdtHeader


typedef struct {
    uint16_t offset0;
    uint16_t segSelector; // Code segment selector in GDT or LDT
    uint8_t ist; // IST is first 3 bits, rest is 0
    uint8_t flags; // Gate type, DPL and present bit
    uint16_t offset1;
    uint32_t offset2;
    uint32_t reserved;

} __attribute__((packed)) IdtEntry_t;



typedef struct {
    uint16_t limit;
    uint64_t base;

} __attribute__((packed)) Idtr_t;




void IdtSetEntry(uint8_t entryNumber, void* handler, uint16_t segmentSelector, uint8_t flags);
void IdtInit(void);
void isrCommonHandler(void);

#endif