#ifndef VM_H__
#define VM_H__

#include <stddef.h>

struct vm_context;

struct vm_context * vm_alloc(size_t capacity);
void                vm_init(struct vm_context *vm, const char *str);
void                vm_free(struct vm_context *vm);
int                 vm_execute(const struct vm_context *vm);

#endif // VM_H__
