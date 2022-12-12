#include <common.h>
#include <string.h>

#define MAX 1024
word_t expr(char *e, bool *success);
void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();
void test();

void test(){
		static char buf[MAX] = {};
    unsigned int show = 0;
    unsigned int length = 0;
    bool *success = (bool*)malloc(sizeof(bool));
    FILE *fp = fopen("../tools/gen-expr/input","r");
    if (fp == NULL){
      printf("Cannot Open The File!!!\n");
      fclose(fp);
      return ;
    }
    while(fgets(buf,MAX,fp)){
      char *exp = strtok(buf," ");
      length = strlen(exp);
      if (buf[length-1] == '\n'){
        buf[length-1] = '\0';
      }   
      show = expr(exp,success); 
      printf("The expr's result is %d\n",show);
    }
    return ;
}

int main(int argc, char *argv[]) {
	test();
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

  /* Start engine. */
  engine_start();

  return is_exit_status_bad();
}
  
  

