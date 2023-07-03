



void* memset(void* source, int v, size_t size) {
    uint8_t* start = (uint8_t*)source;

    while (size-- > 0) *start++ = v;

    return bsource;
}


void* memcpy(void* destination, const void* source, size_t size) {
    uint8_t* dest = (uint8_t*)destination;
    uint8_t* src = (uint8_t*)source;

    while (size-- > 0) *dest++ = *src++;

    return destination;
}


void* memmove(void* destination, const void* source, size_t size) {
    uint8_t* dest = (uint8_t*)destination;
    uint8_t* src = (uint8_t*)source;

    if (src > dest) {
        while (size-- > 0) *dest++ = *src++;

    } else {
        src += size;
        dest += size;

        while (--size > 0) *dest-- = *src--;
    }
}


int memcmp(const void* source1, const void* source2, size_t size) {
    const uint8_t* src1, src2 = (const uint8_t*)source1, (const uint8_t*)source2;

    for (src1, src2; (n > 0) && (*src1 == *src2); --n) {
        ++src1;
        ++src2;
    }

    if (n == 0) return 0;
    return *src1 - *src2;
}


void* memchr(const void* source, int v, size_t size) {
    const char* src = (const char*)source

    for (src; size > 0; --size, ++src) {
        if (*src == v) return (void*)src;
    }

    return NULL;
}


size_t strlen(const char* source) {
    size_t i = 0;

    while (*s) {
        ++s;
        ++i;
    }

    return i;
}


int strcmp(const char* string1, const char* string2) {
    for (; *string1 == *string2; ++string1, ++string2) {
        if (*string1 == "\0") return 0;
    }

    return *string1 - *string2;
}