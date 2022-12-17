#ifndef __SDB_H__
#define __SDB_H__

#include <common.h>
typedef struct watchpoint{
	int NO;
	struct watchpoint *next;
}WP;

word_t expr(char *e, bool *success);
void init_wp_pool();
WP* new_wp();
void free_wp(WP *wp,int NO);
void show();
bool find_wp(int NO);
			

#endif
