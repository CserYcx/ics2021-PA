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

static uint32_t expr_value[32] ;// Expression's value
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
	if (free_ != NULL && free_->next != NULL){
		wp = free_->next;
		free_->next = wp->next;
	}
	assert(free_!=NULL);
	wp->next = NULL;
	//make the wp to the head next and the head has same value with current pointing wp
	if(head != NULL){
		WP *temp = head;
		while(temp != NULL && temp->next != NULL){
			temp = temp->next;
		}
		temp->next = wp;
	}
	else{
		head = (WP*)malloc(sizeof(WP));
		head->NO = -1;
		head->next = wp;
	}
	assert(head != NULL);
	return wp;
}

//free the wp return to the free_
void free_wp(WP *wp,int NO){
	// if free_ is NULL 
	if (free_ == NULL){
		WP* new_fr = (WP*)malloc(sizeof(WP));
		new_fr->NO = -1;
		new_fr->next = wp;	
		free_ = new_fr;
	}
	//free_ is not NULL
	else{
		WP* fr = free_;		
		while(fr->next != NULL){
			if (wp->NO > fr->next->NO){fr = fr->next;}
			else{
				wp->next = fr->next;	
				fr->next = wp;
				break;
			}
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

//pop a list from head
WP* pop_wp(int NO){
	assert(head != NULL);
	WP* h = head;
	while(h != NULL){
		if (NO == h->next->NO){
			WP* wp = h->next;
			h->next = h->next->next;
			memset(wp->expr,0,sizeof(wp->expr));
			printf("pop wp is (NO:%d,Expr:%s,Next:%s)\n",wp->NO,wp->expr,"NULL");
			return wp;
		}
		h = h->next;
	}
	printf("The pop is error!\n");
	return NULL;
}

// as a interface to send a linked list
WP* send_head(){
	WP* wp = head;
	return wp;
}

//As a test programme, to show all element in the head
void show_head(){
	assert(head != NULL);
	WP* wp = head;
	int i = 0;
	printf("That's the head linked list:\n");
	while(wp != NULL){
		printf("(NO:%d,Expr:%s,Next:%d) -> ",wp->NO,(wp->expr != NULL? (wp->expr):"NULL"),(wp->next != NULL? (wp->next->NO):-1));
		wp = wp->next;
		if((i+1)%4 == 0){printf("\n");}
		i++;
	}
	printf("\n");
	
}

//As a test to show all element in free_
void show_free(){
	int i = 0;
	WP* fr = free_;
	printf("That's the free_ linked list:\n"); 
	while(fr != NULL){
		printf("(NO:%d,Expr:%s,Next:%d) -> ",fr->NO,fr->expr,(fr->next != NULL? (fr->next->NO):-1));
		fr = fr->next;
		if((i+1)%4 == 0){printf("\n");}
		i++;
	}
	printf("\n");
}

//In the end of the trace_and_difftest to judge whether every expression's value changed
void scan_and_print(WP* head){
	bool* success = (bool*)malloc(sizeof(bool));
	*success = true;
	assert(head!=NULL);
	WP* temp = head->next;
	if(temp ==NULL){
		Log("No watchpoint can show");
		return ;
	}
	int cnt = 0;
	//Compare every list expression value in head list
	while(temp != NULL){
		uint32_t value = expr(temp->expr,success);
		if(value!= expr_value[cnt] && temp->expr != NULL){
			printf("Watchpoint %d: %s\n",temp->NO,temp->expr);
			printf("Old value == %x\n",expr_value[cnt]);
			printf("New value == %x\n",value);
			expr_value[cnt] = value;
							cnt++;
		}
		temp = temp -> next;
	}
	nemu_state.state = NEMU_STOP;
}

//As a interface in cmd_info, print all watchpoint
void print_watchpoint(){
	if(head == NULL){
		Log("No watchpoint ");
		return;
	}
	WP* wp = head->next;
	assert(wp != NULL);
	while(wp != NULL){
		printf("Watchpoint %d: %s\n", wp->NO, wp->expr);
		wp = wp->next;
	}
}	

