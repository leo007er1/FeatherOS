
#include <Memory/Paging.h>


static volatile struct limine_paging_mode_request pagingRequest = {
    .id = LIMINE_PAGING_MODE_REQUEST,
    .revision = 0,
    .mode = LIMINE_PAGING_MODE_X86_64_4LVL
};


