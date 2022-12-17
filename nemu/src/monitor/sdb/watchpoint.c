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

//typedef struct watchpoint {
 // int NO;
  //struct watchpoint *next;

  /* TODO: Add more members if necessary */

//} WP;

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
//From the free_ 
WP* new_wp(){
	WP* wp = (WP*)malloc(sizeof(WP));
	if (free_ != NULL){
		wp = free_;
		free_ = free_->next;
	}
	assert(free!=NULL);
	assert(wp != NULL);
	wp->next = NULL;
	//make the wp to the head next and the head has same value with current pointing wp
	if(head != NULL){
		WP *temp = head;
		while(temp != NULL && temp->next != NULL){
			temp = temp->next;
			//printf("temp NO is %d\n",temp->NO);
		}
		temp->next = wp;
	}
	if (head == NULL){
		head = (WP*)malloc(sizeof(WP));
		head->NO = -1;
		head->next = wp;
	}
	assert(head != NULL);
	//printf("(%d, %s) -> ",wp->NO,wp->next != NULL?"True":"NULL");
	return wp;
}

//free the wp return to the free_
void free_wp(WP *wp,int NO){
	WP* fr = free_;		
	while(fr != NULL){
		if (wp->NO > fr->NO){
			fr = fr->next;
		}
		else{
			wp->next = fr->next;	
			fr->next = wp;
			break;
		}
	}
}

bool find_wp(int NO){
	WP* h = head;
	while(h != NULL){
		if (NO == h->NO){
			return true;
		}
		h = h->next;
	}
	return false;
}

void show(){
	WP* wp = head;
	int i = 0;
	printf("That's the head linked list:\n");
	while(wp != NULL){
		printf("(%d, %d) -> ",wp->NO,(wp->next != NULL? (wp->next->NO):-1));
		wp = wp->next;
		if((i+1)%4 == 0){printf("\n");}
		i++;
	}
	
	WP* fr = free_;
	printf("That's the free_ linked list:\n"); 
	while(fr != NULL){
		printf("(%d, %d) -> ",fr->NO,(fr->next != NULL? (fr->next->NO):-1));
		fr = fr->next;
		if((i+1)%4 == 0){printf("\n");}
		i++;
	}
}
