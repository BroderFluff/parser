#include "vm.h"
#include "cmd_parse.h"
#include <stddef.h>

enum vm_state {
    VM_CMD_NAME,
    VM_CMD_PARAMS,
    VM_END,
};

struct vm_context {
    int num_insts;
    int inst_base[];
};

struct vm_context *create_vm(int num_insts) {
}

int exec_vm(const struct vm_context *vm)
{
    int current_inst = vm->inst_base[0];
    while (current_inst) {

    }
}

