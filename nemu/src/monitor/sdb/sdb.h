#ifndef __SDB_H__
#define __SDB_H__

#include <common.h>
typedef struct watchpoint{
	int NO;
	char expr[64];
	struct watchpoint *next;
}WP;

word_t expr(char *e, bool *success);
void init_wp_pool();
WP* new_wp();
void free_wp(WP *wp,int NO);
WP* send_head();
void show();
bool find_wp(int NO);
WP* pop_wp(int NO);
			

#endif
