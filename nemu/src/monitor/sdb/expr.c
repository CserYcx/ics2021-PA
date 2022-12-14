#include <isa.h>
#include <stdlib.h>
//POSIX: Portable Operating System Interface
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include <string.h>

//rules type: use the type value to judge which token is what
enum {
  TK_NOTYPE = 256, 
	TK_NOTEQ,
	TK_AND,
	MINUS,
	TK_EQ,
	TK_NUM,
	TK_HEXNUM,
	TK_REG
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
  {"==", TK_EQ},        // equal
	{"!=", TK_NOTEQ},     // not equal
	{"&&", TK_AND},				// and 
  {"\\+", '+'},         // plus
	{"\\-", '-'},					// sub
	{"\\*", '*'},					// multiple
	{"\\/", '/'},					// divide
	{"[1-9][0-9]*|[0-9]", TK_NUM},		// number
	{"^0x[0-9a-fA-F]+", TK_HEXNUM},  // hex number
	{"[\\$]([a-z]|[\\$])+([0-9]+|[a-z]*)", TK_REG}, // reg value
	{"\\(", '('},					// left bracket
	{"\\)", ')'},					// right bracket
};

//NR_REFEX is haved been recognized token number(means having all the recognized rules) 
#define NR_REGEX ARRLEN(rules)
#define MAX_LEN 0xFFFF
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
static Token tokens[MAX_LEN] __attribute__((used)) = {};
//the tokens have been recognized number
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

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;
				//Log("position = %d\n", position);
				//Log("substr_len = %d\n", substr_len);
				//Log("substr_start = %s\n", substr_start);

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
					case '+':  tokens[nr_token++].type = rules[i].token_type;break;
					// the sign '-' may be the sub or the minus 
					case '-': if(position == 1|| tokens[nr_token-1].type <= TK_EQ){
										 tokens[nr_token++].type = MINUS;break;}
										 tokens[nr_token++].type = rules[i].token_type;break;
					case '*':  tokens[nr_token++].type = rules[i].token_type;break;
					case '/':  tokens[nr_token++].type = rules[i].token_type;break;
					case '(':  tokens[nr_token++].type = rules[i].token_type;break;
					case ')':  tokens[nr_token++].type = rules[i].token_type;break;
					case TK_EQ:		tokens[nr_token++].type = rules[i].token_type;break;
					case TK_NOTEQ:tokens[nr_token++].type = rules[i].token_type;break;
					case TK_AND:  tokens[nr_token++].type = rules[i].token_type;break;
					//maybe overflow, remember to rewrite the code 
					case TK_NUM: tokens[nr_token].type = rules[i].token_type;
											 strncpy(tokens[nr_token].str,substr_start,substr_len); 
											 tokens[nr_token].str[substr_len] = '\0';
											 //printf("str is %s\n", tokens[nr_token].str);
											 nr_token++;
											 assert(position <= MAX_LEN); break;
					//the hex number 
					case TK_HEXNUM: tokens[nr_token].type = rules[i].token_type;
													strncpy(tokens[nr_token].str,substr_start,substr_len); 
													tokens[nr_token].str[substr_len] = '\0';
													nr_token++;break;
					//the reg value 
					case TK_REG:		tokens[nr_token].type = rules[i].token_type;
													strncpy(tokens[nr_token].str,substr_start,substr_len); 
													tokens[nr_token].str[substr_len] = '\0';
													nr_token++;break;
          default: //TODO();
        }
        break;
      }
    }

		//out of bound
    if (i == NR_REGEX) {
      Log("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
	
	printf("Make token is over*******************\n");
  return true;
}

/* *****************************************
 * ****the following is my code*************
 * *****************************************/

/*meet the bug1 : the first input: p 80000000 ,result is ok
 *but the next time you input any value,like 1+2 , it will show 
 * 10000000+2 , that's crazy
 * i know the reason because of the damn string copy!!!!!!
 * remember '\0'!!!!false
 *
 * bug2 : if input 2*3+1 , it will do 2*3 + 3+1 , that' sucked!!!
 * the reason is op_pos is real parameter and it can not stay the 
 * data stable(the value will change in every recursion)
 * 
 * bug3 : if input ((2+1)*(1+2)), after first checkparentheses,the expression 
 * will be the (2+1)*(1+2) , then it will get main token and segment fault
 */

//Get the main token and the position
uint32_t get_main_token(Token *token,uint32_t begin,uint32_t end, uint32_t pos){
	// pos to record the current prior token position
	int cnt;
	int flag = 1; //whether the begin is bracket or not, the iteration is ok
	int priority = 0xff;			// current main operator priority 
	int temp_priority= 0xfff;// record the current priority
	
	// to the end
	for(cnt = begin;cnt <= end ;++cnt){
		if(token[cnt].type == 0){
			Log("To the end!!! the currnet pos is %d\n",cnt);
			break;
		}

		// to get the token priority 
		switch(token[cnt].type){
			case '+': temp_priority = 2;break;
			case '-': temp_priority = 2;break;
			case '*': temp_priority = 4;break;
			case '/': temp_priority = 4;break;
			case '(': flag = 0;break;
			case ')': flag = 1;break;
			case TK_EQ:    temp_priority = 1;break;
			case TK_AND:	 temp_priority = 1;break;
			case TK_NOTEQ: temp_priority = 1;break;
			case MINUS:    temp_priority = 6;break;
			default: 
			}

		// the main token priority is the lowest 
		if(flag == 1){	
			if((token[cnt].type > 41 &&token[cnt].type <=47)||(token[cnt].type <= TK_EQ && token[cnt].type >= TK_NOTEQ )){
				if(priority > temp_priority){
					priority = temp_priority;
					pos = cnt;
				}
				//if token's priority is same, choose the farther one
				else if(priority == temp_priority && pos <= cnt){pos = cnt;}
				printf("The current pos is %d\n",pos);
				printf("The current priority is %d\n",priority);
			}
		}
	}
		
	//Error type
	if(priority == 0xff){
		Log("The expression has no operator!!!!!\n");
		assert(0);
	}

	Assert(token[pos].type != TK_NOTYPE && token[pos].type <= TK_EQ, "Token is not operator!!!\n");	
	printf("Get main token is over**********************\n");
	return pos;
}

// the expression should be surrounded with pairs of brackets
bool check_parentheses(uint32_t begin, uint32_t end){
	if(tokens[begin].type != '('){
		return false;
	}

	int outer = 0; // outer is to record whether the out lay is cover by parentheses
	int sum = 0;
	char bracket[32] = {'0'};
	int inner = 0;
	int flag = 0;
	if (tokens[begin].type == '(' && tokens[end].type == ')'){
		outer = 1;
	}
	
	//find every pair of parentheses
	for(int cnt = begin+1; cnt <= end-1;cnt++){
		if(tokens[cnt].type == '('){
			bracket[inner] = '(';
			inner++;
			sum++;
		}
		else if(tokens[cnt].type == ')'){
			bracket[inner] = ')';
			inner++;
			sum--;
		}
		if(sum < 0){
			flag = 1;
		}
	}
	
	if(flag == 1 && outer == 1){printf("The expression is illegal but has a value\n");return false;}
	if(sum > 0){printf("expression is bad!!!\n");assert(0);}
	if(sum == 0 && bracket[0] == '0'){return true;}
	if(sum == 0 && flag == 0 && outer == 1){return true;}
	return false;
}

// operator's position
uint32_t eval(uint32_t begin, uint32_t end){
	if(begin > end){
		// Bad expression 
		Log("That may be the MINUS or the DEREF");
		return 0;
	}
	else if(begin == end){
		// Single tokens
		// The token should be a number
		// return the number value
		printf("the begin = %d\n", begin); 
		if (tokens[begin].type == TK_NUM){
			Assert(tokens[begin].str, "The num is none!!!\n");
			printf("the string is %s\n", tokens[begin].str);
			printf("the nums value is %d\n", atoi(tokens[begin].str));
			return atoi(tokens[begin].str);
		}
		else if (tokens[begin].type == TK_HEXNUM){
			Assert(tokens[begin].str, "The num is none!!!\n");
			printf("the string is %s\n", tokens[begin].str);
			printf("the nums value is %s\n", tokens[begin].str);
			return strtol(tokens[begin].str,NULL,16);
		}
		else if (tokens[begin].type == TK_REG){
			bool* success = (bool*)malloc(sizeof(bool));
			*success = true;
			Assert(tokens[begin].str, "The num is none!!!\n");
			printf("the string is %s\n", tokens[begin].str);
			printf("the nums value is %s\n", tokens[begin].str+1);
			return isa_reg_str2val(tokens[begin].str+1,success); 
		}
		else{ 
			Log("The token is not a number!!!");
			return -1;
		}
	}

	else if(check_parentheses(begin,end) == true){
		//  Expression is surronded by a matched pair of parentheses
		//  in the case , throw away the parentheses
		printf("the current begin is %d, end is %d\n",begin,end);
		return eval(begin+1,end-1);
	}

	else { 
		uint32_t op_pos = 0;
		//Log("Begining find the main token!!\n");
		op_pos = get_main_token(tokens,begin,end,op_pos);
		uint32_t val1 = eval(begin, op_pos-1);	
		uint32_t val2 = eval(op_pos + 1,end);	
		printf("val1 = %d, val2 = %d\n",val1,val2);
		printf("type = %c\n",tokens[op_pos].type);
		switch (tokens[op_pos].type){
			case '+': return val1 + val2;
			case '-': return val1 - val2;
			case '*': return val1 * val2;
			case '/': return val1 / val2;
			case TK_EQ:    return val1 == val2;
			case TK_NOTEQ: return val1 != val2;
			case TK_AND:   return val1 && val2;
			case MINUS:    return -val2;
			default:Log("The damn fault!"); assert(0);
			}
	}
	return 0;
}


word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  //TODO();
	/*int cnt = 0;
	printf("token str is: ");
	while(tokens[cnt].type != 0){
	printf("%s", tokens[cnt].str);
	cnt++;
	}
	printf("\n");*/
	return eval(0,nr_token-1);
}
