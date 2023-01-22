#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  panic("Not implemented");
}

char *strcpy(char *dst, const char *src) {
  panic("Not implemented");
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  panic("Not implemented");
}

/*
 * return integer to indicate the result of comparsion
 * 1. 0, if s1 equals to s2
 * (return the first symbol ascii D-value)
 * 2. a negative value if s1 is less than s2
 * 3. a positive value if s1 is greater than s2
 */
int strcmp(const char *s1, const char *s2) {
  int s1len = sizeof(s1);
  int s2len = sizeof(s2);
  if (s1len < s2len){
    return ' '-s2[s1len];
  }
  else if (s1len > s2len){
    return s1[s2len];
  }
  else{
    for(int i = 0;i<s1len;++i){
      if(s1[i] == s2[i]){
        continue;
      }
      else {
        return s1[i] - s2[i];
      }
    }
  }
  return 0;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  panic("Not implemented");
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  panic("Not implemented");
}

int memcmp(const void *s1, const void *s2, size_t n) {
  panic("Not implemented");
}

#endif
