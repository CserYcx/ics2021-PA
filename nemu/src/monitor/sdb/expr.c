#include <isa.h>
#include <stdlib.h>
//POSIX: Portable Operating System Interface
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

//rules type: use the type value to judge which token is what
enum {
  TK_NOTYPE = 256, TK_EQ,TK_NUM

  /* TODO: Add more token types */

};

static struct rule {
	//regex is regular expression
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal
	{"\\-", '-'},					// sub
	{"\\*", '*'},					// multiple
	{"\\/", '/'},					// divide
	{"[0-9]+", TK_NUM},		// number
	{"\\(", '('},					// left bracket
	{"\\)", ')'},					// right bracket
};

//NR_REFEX is haved been recognized token number(means having all the recognized rules) 
#define NR_REGEX ARRLEN(rules)

//re is to store the token has been recognized and regcomp will compile them
static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
	//Think, if str overflows , how to solve the problem
  char str[32];
} Token;

//__attribute__((used)) means that the variable must be emitted even if it appears that the variable is not referenced.
static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
	// regmatch_t is a struct that has two members: rm_so to match the string's beginning,
	// rm_eo to match the string's end
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
			//match target string
			//ignore the line feed
			//int regexec(regex_t *compiled,char *string,size_t nmatch,regmatch_t matchptr [],int flags)
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;
				printf("substr_len = %d\n", substr_len);

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;
				printf("position = %d\n", position);

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
					case '+': tokens[i].type = rules[i].token_type;break;
					case '-': tokens[i].type = rules[i].token_type;break;
					case '*': tokens[i].type = rules[i].token_type;break;
					case '/': tokens[i].type = rules[i].token_type;break;
					case TK_NOTYPE: break;
					case TK_NUM: tokens[i].type = rules[i].token_type;
					//maybe overflow, remember to rewrite the code 
											 strcpy(tokens[i].str, e+position); 
											 assert(position <= 32); break;
          default: TODO();
        }

        break;
      }
    }

		//out of bound
    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

//Get the main token and the position
Token get_main_token(Token *token, uint32_t* pos){
	// pos to record the current prior token position
	int cnt;
	int priority = 0;			// depend on priority to choose the main token 
	int temp_priority = 0;// record the current priority
	for(cnt = 0;cnt < 32;++cnt){
		if(token[cnt].str == NULL){
			break;
		}
		// to get the token priority 
		if(token[cnt].type >= 42 || token[cnt].type <= 47){
			switch(token[cnt].type){
				case '+': priority = 1;break;
				case '-': priority = 1;break;
				case '*': priority = 2;break;
				case '/': priority = 2;break;
			}
		}
		if(priority > temp_priority){*pos = cnt;}
		//if token's priority is same, choose the farther one
		else if(priority == temp_priority && *pos <= cnt){*pos = cnt;}
	}
	assert(token[*pos].str != NULL);
	return token[*pos];
}



uint32_t eval(uint32_t begin, uint32_t end){
	if(begin > end){
		// Bad expression 
		Log("That is a bad expression");
		return 0;
	}
	else if(begin == end){
		// Single tokens
		// The token should be a number
		// return the number value
		 
		if (tokens[begin].type != TK_NUM){
			Log("The token is not a number!!!");
			return 0;
		}
		else{
			assert(atoi(tokens[begin].str));
			return atoi(tokens[begin].str);
		}
	}
	/*else if(check_parentheses(begin,end) == true){
		//  Expression is surronded by a matched pair of parentheses
		//  in the case , throw away the parentheses
		// 
		eval(begin+1,end-1);
	}*/
	else{
		//printf("Begining find the main token!!");
		uint32_t op_pos = 0;
		Token op = get_main_token(tokens,&op_pos);
		uint32_t val1 = eval(begin, op_pos -1);	
		uint32_t val2 = eval(op_pos + 1,end);	
		switch (op.type){
			case '+': return val1 + val2;
			case '-': return val1 - val2;
			case '*': return val1 * val2;
			case '/': return val1 / val2;
			default:Log("The damn fault!"); assert(0);
			}
	}
}


word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  TODO();

	return eval(0,strlen(e));
}
