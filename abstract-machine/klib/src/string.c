#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  panic("Not implemented");
}

char *strcpy(char *dst, const char *src) {
  assert(src != NULL && dst != NULL);
  char *ret = dst;
  // original function will be overflow, here is similar
  while((*dst++ = *src++) != '\0');
  return ret;
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  assert(dst != NULL && src != NULL);
  int srclen = sizeof(src);
  int dstlen = sizeof(dst);
  int i = 0;
  for(;i<srclen && src[i] != '\0';++i){
    dst[dstlen + i] = src[i];
  }
  dst[dstlen + i] = '\0';
  return dst;
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
  if(!n){
    return 0;
  }
  char *xs = (char *)s;
  for(int i=0;i<n;++i){
    *(xs+i) = c;
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
}

#endif
