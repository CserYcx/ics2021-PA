#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>


//The BUG:
//Avoid to cover the buf, we need a cnt to record the newest location,but if we 
//count every cnt after call the gen function, it will ignore some string, such as Calling
//a lot of function in one case

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

//To avoid cover the old data, use a global parameter and a function 
//to record where the buf newest address
uint32_t count = 0;
uint32_t length = 0;

uint32_t len(uint32_t num){
	int cnt = 0;
	while(num/10 != 0){
		cnt++;
		num = num/10;
	}
	return cnt+1;
}

//give a unsigned number is not greater than the num
uint32_t choose(uint32_t num){
	uint32_t rand_num = rand() % num;
	return rand_num;
}

//generate the number
static void gen_num(){
	uint32_t rand_num = rand();
	if(*(buf+count+length-1)=='/' && rand_num == 0){
		sprintf(buf+count+length,"%d",1);
		length = length+1;
	}
	else{
		sprintf(buf+count+length,"%d",rand_num);
		length = length+len(rand_num);
	}
}

//generate the expression with the parentheses
static void gen_left_bracket(){	
	char left_bracket = '(';
	sprintf(buf+count+length,"%c",left_bracket);
	length = length+1;
}

static void gen_right_bracket(){	
	char right_bracket = ')';
	sprintf(buf+count+length,"%c",right_bracket);
	length = length+1;
}

static void gen_op(){
	uint32_t rand_num = rand()%4;
	switch(rand_num){
		case 0:	sprintf(buf+count+length,"%c",'+');length = length+1;break;
		case 1:	sprintf(buf+count+length,"%c",'-');length = length+1;break;
		case 2:	sprintf(buf+count+length,"%c",'*');length = length+1;break;
		default :	sprintf(buf+count+length,"%c",'/');length = length+1;break;
	}		
}


static void gen_rand_expr() {
  //buf[0] = '\0';
	switch(choose(3)){
		case 0: gen_num();break;
		case 1: gen_left_bracket();gen_num();gen_right_bracket();break;
		default: gen_rand_expr();gen_op();gen_rand_expr();break;
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

		//put the data from the buf into code_buf
    sprintf(code_buf, code_format, buf+count);

		//build a new c txt with the code_format 
    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);// write the code_buf data into the /tmp/.code.c
    fclose(fp);

		//execute shell command 
    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf+count);
		if(count + length <= 0xffff-1){count = count + length;} 
		else{count = 0;}//prevent buf overflow
		length = 0; // for the next loop to calculate the length
  }
  return 0;
}
