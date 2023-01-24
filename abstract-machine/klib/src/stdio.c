#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  // variadic list
  va_list ap;
  char *ret = out;
  va_start(ap,fmt);
  for(int i = 0;i<sizeof(fmt);++i){
    char *s;
    if(fmt[i] == '%'){
      switch (fmt[i+1])
      {
      case 'd':
        s = va_arg(ap,char *);
        for(int j=0;j<sizeof(s);++j)
          *ret++ = *s++;
        ++i;
        break;
      
      case 's':
        s = va_arg(ap,char *);
        for(int j=0;j<sizeof(s);++j)
          *ret++ = *s++;
        ++i;
        break;
      
      default:
        panic("To be completed");
        break;
      }
    }
    else{
      *ret++ = fmt[i];
    }
  }
  *ret = '\0';
  va_end(ap);
  return 0;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
