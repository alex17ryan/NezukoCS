#ifndef NEZUKOCS_H
#define NEZUKOCS_H

#include <stdio.h>
#include <stdlib.h>

// Types and Structures
typedef enum __nezuko_error {
    FAILED_ALLOCATION,
    OUT_RANGED_SIZE,
    TARGET_NOT_FOUND,
    EMPTY_TODO
} __nzk_err;

typedef struct __nezuko_task {
    void *nzk_task;
    unsigned long long nzk_t_size;
    struct __nezuko_task *nzk_t_link;
} __nzk_t;

typedef struct __nezuko_task_stack {
    __nzk_t *nzk_t_s_top;
    unsigned long long nzk_t_s_size;
} __nzk_t_s;

// Prototypes
void __nzk_err_msg(__nzk_err);

void *__malloc_s(unsigned long long);

void __initialize_nzk_t_stack();
void __deinitialize_nzk_t_stack();

__nzk_t *__create_nzk_t(void *, unsigned long long);
void __kill_nzk_t(__nzk_t *);

void __append_nzk_t_s(__nzk_t *);
void __pop_nzk_t_s();
void __delete_nzk_t(void *);

void *__allocate_space(unsigned long long);
void __deallocate_space(void *);

void __empty_nzk_t_s();

// Globals
__nzk_t_s *__nzk_todo = NULL;

// Functions
void __nzk_err_msg(__nzk_err nzk_err) {
    printf("\nNezukoCS\\Error: ");
    switch (nzk_err) {
    case FAILED_ALLOCATION:
        printf("Space allocation failed.");
        break;
    case OUT_RANGED_SIZE:
        printf("Space size is out of range.");
        break;
    case TARGET_NOT_FOUND:
        printf("Allocated space address not found.");
        break;
    case EMPTY_TODO:
        printf("No allocated space is tracked.");
        break;
    default:
        printf("This error code is not on Nezoko's list.");
    }
    exit(EXIT_FAILURE);
}

void *__malloc_s(unsigned long long allocated_space_size) {
    if ((long long)allocated_space_size > 0) {
        void *allocated_space = malloc(allocated_space_size);
        if (allocated_space) {
            return allocated_space;
        } else {
            __nzk_err_msg(FAILED_ALLOCATION);
        }
    } else {
        __nzk_err_msg(OUT_RANGED_SIZE);
    }
    return NULL;
}

void __initialize_nzk_t_stack() {
    __nzk_todo = (__nzk_t_s *)__malloc_s(sizeof(__nzk_t_s));
    __nzk_todo->nzk_t_s_top = NULL;
    __nzk_todo->nzk_t_s_size = 0;
};

void __deinitialize_nzk_t_stack() {
    free(__nzk_todo);
    __nzk_todo = NULL;
}

__nzk_t *__create_nzk_t(void *nzk_task, unsigned long long nzk_t_size) {
    __nzk_t *new_nzk_t = (__nzk_t *)__malloc_s(sizeof(__nzk_t));
    new_nzk_t->nzk_task = nzk_task;
    new_nzk_t->nzk_t_size = nzk_t_size;
    new_nzk_t->nzk_t_link = NULL;
    return new_nzk_t;
}

void __kill_nzk_t(__nzk_t *targeted_nzk_t) {
    free(targeted_nzk_t->nzk_task);
    targeted_nzk_t->nzk_task = NULL;
    free(targeted_nzk_t);
}

void __append_nzk_t_s(__nzk_t *new_nzk_t) {
    new_nzk_t->nzk_t_link = __nzk_todo->nzk_t_s_top;
    __nzk_todo->nzk_t_s_top = new_nzk_t;
    __nzk_todo->nzk_t_s_size += new_nzk_t->nzk_t_size;
}

void __pop_nzk_t_s() {
    __nzk_t *new_nzk_t_s_top = __nzk_todo->nzk_t_s_top->nzk_t_link;
    unsigned long long nzk_t_s_top_size = __nzk_todo->nzk_t_s_top->nzk_t_size;
    __kill_nzk_t(__nzk_todo->nzk_t_s_top);
    __nzk_todo->nzk_t_s_size -= nzk_t_s_top_size;
    __nzk_todo->nzk_t_s_top = new_nzk_t_s_top;
}

void __delete_nzk_t(void *targeted_nzk_t) {
    __nzk_t *nzk_t_previous_cursor = __nzk_todo->nzk_t_s_top;
    __nzk_t *nzk_t_cursor = __nzk_todo->nzk_t_s_top->nzk_t_link;
    while (nzk_t_cursor && nzk_t_cursor->nzk_task != targeted_nzk_t) {
        nzk_t_previous_cursor = nzk_t_cursor;
        nzk_t_cursor = nzk_t_cursor->nzk_t_link;
    }
    if (nzk_t_cursor->nzk_task == targeted_nzk_t) {
        nzk_t_previous_cursor->nzk_t_link = nzk_t_cursor->nzk_t_link;
        unsigned long long nzk_t_size = nzk_t_cursor->nzk_t_size;
        __kill_nzk_t(nzk_t_cursor);
        __nzk_todo->nzk_t_s_size -= nzk_t_size;
    } else {
        __nzk_err_msg(TARGET_NOT_FOUND);
    }
}

void *__allocate_space(unsigned long long allocated_space_size) {
    if (!__nzk_todo) {
        __initialize_nzk_t_stack();
    }
    void *allocated_space = __malloc_s(allocated_space_size);
    __append_nzk_t_s(__create_nzk_t(allocated_space, allocated_space_size));
    return allocated_space;
}

void __deallocate_space(void *allocated_space) {
    if (__nzk_todo && __nzk_todo->nzk_t_s_size) {
        if (__nzk_todo->nzk_t_s_top->nzk_task == allocated_space) {
            __pop_nzk_t_s();
        } else {
            __delete_nzk_t(allocated_space);
        }
    } else {
        __nzk_err_msg(EMPTY_TODO);
    }
}

void __empty_nzk_t_s() {
    if (__nzk_todo) {
        if (__nzk_todo->nzk_t_s_size) {
            unsigned long long nzk_t_s_size = __nzk_todo->nzk_t_s_size;
            while (__nzk_todo->nzk_t_s_size) {
                __pop_nzk_t_s();
            }
            printf("\nNezuko cleaned %lli bytes of allocated memory.", nzk_t_s_size);
        } else {
            printf("\nIt looks like there's nothing left for Nezuko to clean! Good job.");
        }
        __deinitialize_nzk_t_stack();
    } else {
        printf("\nNezuko cleaning services were not needed.");
    }
}

// Interfaces
void* allocate(unsigned long long allocated_space_size) {
    return __allocate_space(allocated_space_size);
}

void deallocate(void* allocated_space) {
    __deallocate_space(allocated_space);
}

int nezuko() {
    __empty_nzk_t_s();
    return 0;
}

#endif