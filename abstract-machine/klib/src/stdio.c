#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  char *str;

  for(str = out;*fmt;fmt++){
    if(*fmt != '%'){
      *str++ = *fmt;
      continue;
    }
    else{
      fmt++;
      switch (*fmt)
      {
      case 's':
        char *s = va_arg(ap,char *);
        int len = strlen(s);
        for(int i = 0;i<len;++i){
          *str++ = *s++;
        }
        break;

      case 'd':
        int val = va_arg(ap,int);
        for(int i = 1000000000;i>0;i/=10){
          if(val/i == 0 && val != 0){
            continue;
          }
          else{
            *str++ = val/i + 0x30;
            val = val%i;
          }
        }
        break;
      
      default:
        break;
      }
    }
  }

  *str = '\0';
  return str - out;
}

int sprintf(char *out, const char *fmt, ...) {
  // variadic list
  va_list ap;
  int val;

  va_start(ap,fmt);
  val = vsprintf(out,fmt,ap);
  va_end(ap);
  
  return val;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
