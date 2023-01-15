#include <am.h>
#include <nemu.h>

extern char _heap_start;
int main(const char *args);

// point to the begin of heap and end of heap
// use the heap, we can dynamic allocate the memory for our program
Area heap = RANGE(&_heap_start, PMEM_END);
#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;

// print out a char
void putch(char ch) {
  outb(SERIAL_PORT, ch);
}

// end the program work
void halt(int code) {
  nemu_trap(code);

  // should not reach here
  while (1);
}

// do some TRM initial work
void _trm_init() {
  int ret = main(mainargs);
  halt(ret);
}
