#ifndef VM_H__
#define VM_H__

struct vm_context;

struct vm_context * create_vm(int num_inst);
void                destroy_vm();
int                 exec_vm(struct vm_context *vm);

#endif // VM_H__
