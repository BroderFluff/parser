#include <stdlib.h>
#include <stdio.h>
#include "vm.h"
#include "cmd_parse.h"

int main(void)
{
    struct vm_context *vm = vm_alloc(256);
    vm_init(vm, "  setLEDCount 20\n   setLEDCount 19");
    vm_execute(vm);
    vm_free(vm);
}

