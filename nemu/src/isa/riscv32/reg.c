#include <isa.h>
#include "local-include/reg.h"
#include "string.h"

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
	// print the registers' value
	for(int cnt = 0;cnt<32;++cnt){
		printf("%4s = %u  \n",regs[cnt],gpr(cnt));
	}

}

word_t isa_reg_str2val(const char *s, bool *success) {
	int result = 0;
	for(int cnt = 0;cnt<32;++cnt){
		if(strcmp(regs[cnt],s)==0){
			result = gpr(cnt);	
		}
	}
  return result;
}
