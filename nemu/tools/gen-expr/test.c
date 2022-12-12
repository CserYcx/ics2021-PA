#include <stdio.h>
#include <string.h>
#include "/home/cracker/ics2021/nemu/src/monitor/sdb/sdb.h"
#include <stdlib.h>

#define MAX 1024

word_t expr(char *e, bool *success);

int main(){
	char *exp ;
	unsigned int show = 0;
	unsigned int length = 0;
	bool *success = (bool*)malloc(sizof(bool));
	FILE *fp = fopen(input,"r");
	if (fp == NULL){
		printf("Cannot Open The File!!!\n");
		fclose(fp);
		return 0;
	}
	while(fgets(buf,MAX,fp)){
		exp = strtok(buf," ");
		length = strlen(exp);
		if (buf[length-1] == '\n'){
			buf[length-1] = '\0';
		}
		show = expr(exp,success);	
		printf("The expr's result is %d\n",show);
	}
	return 0;
}
