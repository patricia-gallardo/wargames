#include <unistd.h>
#include <fcntl.h>

/**
 * clang -o shellcode shellcode.c
 * ./shellcode
 */
int main(void) {
  close(0);
  open("/dev/tty", O_RDWR);
  char *name[2];
  name[0] = "/bin/sh";
  name[1] = NULL;
  execve(name[0], name, NULL);
}