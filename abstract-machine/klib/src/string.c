#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  const char *p = s;
  while(*p != '\0')
    p++;
  return ((size_t)(p-s));
}

char *strcpy(char *dst, const char *src) {
  assert(src != NULL || dst != NULL);
  // original function will be overflow, here is similar
  char *ret = dst;
  while((*dst++ = *src++) != '\0');
  return ret;
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  assert(dst != NULL && src != NULL);
  char *ret = dst;
  while(*dst) 
    dst++;
  while((*dst++ = *src++) != '\0');
  
  return ret;
}

/*
 * return integer to indicate the result of comparsion
 * 1. 0, if s1 equals to s2
 * (return the first symbol ascii D-value)
 * 2. a negative value if s1 is less than s2
 * 3. a positive value if s1 is greater than s2
 */
int strcmp(const char *s1, const char *s2) {
  while(*s1 && (*s1 == *s2)){
    ++s1;
    ++s2;
  }
  return *s1 - *s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  if(n == 0){
    return 0;
  }
  const unsigned char uc = c;
  unsigned char *xs = s;
  while(n--){
    *xs = uc;
    xs++;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  panic("Not implemented");
}

int memcmp(const void *s1, const void *s2, size_t n) {
  if(n == 0){
    return 0;
  }
  const unsigned char *xs1 = s1;
  const unsigned char *xs2 = s2;
  while(--n && *xs1 == *xs2){
    xs1 ++;
    xs2 ++;
  }
  return (*xs1 - *xs2);
}

#endif
