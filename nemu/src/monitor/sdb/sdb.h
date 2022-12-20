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

WP* new_wp();// create a new watchpoint
void free_wp(WP *wp,int NO); // release a watchpoint
WP* send_head(); // return the head linked list
void show();     // print head list and free_ list
bool find_wp(int NO); //judge whether a watchpoint is in head
WP* pop_wp(int NO);   //pop a watchpoint in head
void scan_and_print(WP* wp); // scan all watchpoints and print the watchpoints whose value changed


#endif
