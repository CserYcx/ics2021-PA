#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include </home/cracker/ics2021/nemu/include/memory/host.h>

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
//line read and return the string for the next cut
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

int string_turn_int(char *arg){
		int next = 0;
		while((int)*arg != 0){
				next = (int)*arg-48+next*10;
				arg = arg+1;
		}
		assert(next);
		return next;
}


static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  return -1;
}

static int cmd_si(char *args){
	//cut the string
	char *arg = strtok(NULL, " ");
		int num = 0;
  if (arg == NULL) {
    /* no argument given */
		cpu_exec(1);
  }
  else {
		num = string_turn_int(arg);
		cpu_exec(num);
		assert(num);
  }
  return 0;
}

static int cmd_info(char *args);

static int cmd_help(char *args);

static int cmd_x(char *args);
//static int cmd_x(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },

  /* TODO: Add more commands */
	{"si", "Make the program execute N pieces instructions and stop, if N is null, default 1", cmd_si},
	{"info", "Print the register state, or print the watchpoint information", cmd_info},
	{"x", "Calculate the expression's value and make it to be the start of memory address. Then outputs N 4-bytes in hex form", cmd_x},

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

static int cmd_info(char *args){
  char *arg = strtok(NULL," ");
	assert(arg != NULL);
	if(arg == NULL){   
		printf("%s - %s\n", cmd_table[4].name, cmd_table[4].description);
		}
	else if (strcmp(arg,"r")==0){
		isa_reg_display();
		}
	return 0;
}

static int cmd_x(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int next = 0;
	uint32_t show = 0;
	long long *addr_int = (long long *)malloc(sizeof(long long));
  if (arg == NULL) {
    /* no argument given */
		printf("%s - %s\n", cmd_table[5].name, cmd_table[5].description);
  }
  else {
			// the next stores n for address to show nth 4-byte memory 
			assert(arg != NULL);
			next = string_turn_int(arg);
			printf("next = %d\n",next);
			arg = strtok(NULL, " ");
			assert(arg != NULL);
			//*addr_int = string_turn_int(arg+2);
			sscanf(arg,"%llx",addr_int);
			printf("%lld\n",*addr_int);
			for(int cnt=0;cnt<next;cnt++){
				printf("val = %u",*(unsigned int *)addr_int);
				printf("!!!!ad p");
				assert((void *)(*addr_int));
				show = host_read((void *)(*addr_int),4);

				printf("0x%016x   \n",show);
				printf("%d \n",show);
			}
  }
  return 0;
}


void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
