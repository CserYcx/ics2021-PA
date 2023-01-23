#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  panic("Not implemented");
}

char *strcpy(char *dst, const char *src) {
  panic("Not implemented");
  /*
  assert(src != NULL && dst != NULL);
  // original function will be overflow, here is similar
  char *ret = dst;
  while((*dst++ = *src++) != '\0');
  return ret;
  */
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  panic("Not implemented");
  /*
  assert(dst != NULL && src != NULL);
  strcpy(dst + sizeof(dst),src);
  return dst;
  */
}

/*
 * return integer to indicate the result of comparsion
 * 1. 0, if s1 equals to s2
 * (return the first symbol ascii D-value)
 * 2. a negative value if s1 is less than s2
 * 3. a positive value if s1 is greater than s2
 */
int strcmp(const char *s1, const char *s2) {
  assert(s1 != NULL && s2 != NULL);
  const unsigned char *p1 = (const unsigned char *)s1; 
  const unsigned char *p2 = (const unsigned char *)s2; 
  unsigned char c1, c2;
  do{
    c1 = (unsigned char) *p1++;
    c2 = (unsigned char) *p2++;
    if(c1 == '\0'){
      return c1 - c2;
    }
  }while(c1 == c2);

  return 1;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  panic("Not implemented");
  /*
  if(!n){
    return 0;
  }
  const unsigned char uc = (const unsigned char)c;
  unsigned char *xs = (unsigned char *)s;
  while(n--){
    *xs++ = uc;
  }
  return s;
  */
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  panic("Not implemented");
}

int memcmp(const void *s1, const void *s2, size_t n) {
  panic("Not implemented");
  /*
  if(!n){
    return 0;
  }
  char *xs1 = (char *)s1;
  char *xs2 = (char *)s2;
  while(n-- && *xs1 == *xs2){
    xs1 += 1;
    xs2 += 1;
  }
  return (*(unsigned char *)xs1 - *(unsigned char *)xs2);
  */
}

#endif
