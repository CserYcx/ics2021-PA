#include "sdb.h"
/******* The Task**********
 * to write two functions 
 * WP* new_wp();
 * void free_wp(WP *wp)
 * new_wp is to return a spare function from the free list
 * free_wp return the wp to the free_
 * *************************/

//Linked list size
#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */

} WP;

static WP wp_pool[NR_WP] = {};
//head is to organize the using node
//free_ is to organize the spare node
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

