#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

uint32_t choose(uint32_t num){
	int rand_num = rand() % num;
	return rand_num;
}

static void gen_num(){
	int rand_num = rand();
		
}

static void gen_rand_expr() {
  //buf[0] = '\0';
	switch(choose(3)){
		case 0: gen_num();break;
		default:break;
		}
}

int main(int argc, char *argv[]) {
	//time(0) is to return the system's time
  int seed = time(0);
  srand(seed);// create the random number
  int loop = 1;
	//loop is how many number you want to create
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

		//build a new c txt with the code_format 
    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

		//execute shell command 
    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
