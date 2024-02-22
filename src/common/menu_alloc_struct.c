#include "memory.h"
#include "object.h"

void* allocStruct(const char* name, u32 size) {
    void* data;

    if (isMenuDataHeapActive()) {
        data = (*heap_alloc)(HEAP_KIND_MENU_DATA, size);
        if (data == NULL) {
            data = (*heap_alloc)(HEAP_KIND_MULTIPURPOSE, size);
        } else {
            // Empty else needed for matching
        }
    } else {
        data = (*heap_alloc)(HEAP_KIND_MULTIPURPOSE, size);
    }
    return data;
}

void* func_8013B33C_BE52C(const char* name, u32 size) {
    void* data;

    if (isMenuDataHeapActive()) {
        data = (*func_80001008_1C08)(HEAP_KIND_MENU_DATA, size);
        if (data == NULL) {
            data = (*func_80001008_1C08)(HEAP_KIND_MULTIPURPOSE, size);
        } else {
            // Empty else needed for matching
        }
    } else {
        data = (*func_80001008_1C08)(HEAP_KIND_MULTIPURPOSE, size);
    }
    return data;
}

void* allocStructInObjectEntryList(
    const char* name, cv64_object_t* object, u32 size, s32 alloc_data_index
) {
    void* data;
    u32 temp;

    if (isMenuDataHeapActive()) {
        data = (*object_allocEntryInList)(
            object, HEAP_KIND_MENU_DATA, size, alloc_data_index
        );
        if (data == NULL) {
            data = (*object_allocEntryInList)(
                object, HEAP_KIND_MULTIPURPOSE, size, alloc_data_index
            );
        } else {
            // Empty else needed for matching
        }
    } else {
        data = (*object_allocEntryInList)(
            object, HEAP_KIND_MULTIPURPOSE, size, alloc_data_index
        );
    }
    return data;
}

void* func_8013B454_BE644(
    const char* name, cv64_object_t* object, u32 size, s32 alloc_data_index
) {
    void* data;
    u32 temp;

    if (isMenuDataHeapActive()) {
        data = (*func_80002264_2E64)(
            object, HEAP_KIND_MENU_DATA, size, alloc_data_index
        );
        if (data == NULL) {
            data = (*func_80002264_2E64)(
                object, HEAP_KIND_MULTIPURPOSE, size, alloc_data_index
            );
        } else {
            // Empty else needed for matching
        }
    } else {
        data = (*func_80002264_2E64)(
            object, HEAP_KIND_MULTIPURPOSE, size, alloc_data_index
        );
    }
    return data;
}

void func_8013B4F0_BE6E0() {
    if (isMenuDataHeapActive()) {
        func_80000D68_1968(HEAP_KIND_MENU_DATA, 0xC0000000);
    }
}

u32 isMenuDataHeapActive() {
    u32 is_active;

    is_active = heaps[HEAP_KIND_MENU_DATA].flags & HEAP_ACTIVE;
    if (is_active == FALSE) {
        return FALSE;
    }
    return TRUE;
}
