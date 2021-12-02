#include <stdio.h>
#include <ctype.h>

//variables
int charClass;
int lexLen;
int token;
int nextToken;
int _float=0;
char lexeme[100];
char nextChar;
char prevChar;
FILE *in_fp;

//function dec
int lookup(char ch);
void addChar(void);
void getChar(void);
void getSet(void); 
int lex(void);

//Char class
#define LETTER 0
#define DIGIT 1
#define FLOAT 2
#define FOR 3

#define UNKNOWN 99

//tokens
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define DOT 3
#define FOR_CODE 30
#define IF_CODE 31
#define ELSE_CODE 32 
#define WHILE_CODE 33
#define DO_CODE 34 
#define INT_CODE 35 
#define FLOAT_CODE 36
#define SWITCH_CODE 37
#define MOD_OP 38
#define LEFT_BLOCK 39
#define RIGHT_BLOCK 40
#define LESS_CODE 41
#define GREATER_THAN_CODE 42
#define RETURN_CODE 43
#define FOREACH_CODE 55
#define COLON_CODE 46
#define SEMICOLON_CODE 45


void factor(void);

void void_check(void);

void main_check(void);

void block_check(void);
void statement(void);

void error(void){
  printf("Error1\n");
  nextToken = EOF;
}
void error2(void){
    nextToken = EOF;
}

// main driver
int main(void) {
	
	 if ((in_fp = fopen("front.in", "r")) == NULL)
	 	printf("ERROR unable to open front.in \n");
	 else {
	 	getChar();
     printf("Enter <program>\n");
	 do {
	 	lex();
     void_check();


	 } while (nextToken != EOF);

	 }
   printf("Exit <program>\n");
	 return 0;
}

//look up operator and parantheses and return token
int lookup(char ch) {
  
	 switch (ch) {
		  case ':':
			 addChar();
			 nextToken = COLON_CODE;
       
			 break;
      case ';':
			 addChar();
			 nextToken = SEMICOLON_CODE;
       
			 break;
      case '=':
			 addChar();
			 nextToken = ASSIGN_OP;
       
			 break;
      case '{':
			 addChar();
			 nextToken = LEFT_BLOCK;
       
			 break;
		 case '}':
			 addChar();
			 nextToken = RIGHT_BLOCK;
			 break;
     case '(':
			 addChar();
			 nextToken = LEFT_PAREN;
       
			 break;
		 case ')':
			 addChar();
			 nextToken = RIGHT_PAREN;
			 break;
		 case '+':
			 addChar();
			 nextToken = ADD_OP;
			 break;
		 case '-':
			 addChar();
			 nextToken = SUB_OP;
			 break;
		 case '*':
			 addChar();
			 nextToken = MULT_OP;
			 break;
		 case '/':
			 addChar();
			 nextToken = DIV_OP;
			 break;

    case '%':
			 addChar();
			 nextToken = MOD_OP;
			 break;
       
		 default:
			 addChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

//addChar
void addChar(void) {
  
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
    //printf("%c",nextChar);
    lexeme[lexLen] = '\0';
    
	}
   
   else
	printf("ERROR lexeme too long \n");
}


//getChar
void getChar(void) {
    
	 if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar))
		 	charClass = LETTER;
		 else if (isdigit(nextChar) ){
       charClass = DIGIT;
       }
       else if (nextChar=='.' ){
         charClass = FLOAT;
       }
       
       
		 else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
}


//getSet - retrieves non-blank character
void getSet(void) {
  
	while (isspace(nextChar)){
	getChar();
   
}
_float=0;

}

//parse factor

 void term(void) {
	 printf("Enter <term>\n");
	
	 factor();
	//parse factor if * or /
	 while (nextToken == MULT_OP || nextToken == DIV_OP|| nextToken == MOD_OP|| nextToken == ASSIGN_OP) {
		 lex();
		 factor();
	 }
	 printf("Exit <term>\n");
}
int lex(void) {
 
	 lexLen = 0;
	 getSet();
	 switch (charClass) {
		// identifiers
		 case LETTER:
     addChar();
     getChar();
      
			 while (charClass == LETTER ||charClass == DIGIT ||nextChar == '.'   ||nextChar =='e'||nextChar =='E') {
         addChar();
         getChar();
         
			 }
       if(lexeme[0] == 'f'&& lexeme[1] == 'o'&& lexeme[2] == 'r' && lexeme[3]!='e'){
           nextToken = FOR_CODE;
			 break;
         }else if(lexeme[0] == 'i'&& lexeme[1] == 'f'){
           nextToken = IF_CODE;
			 break;
         }else if(lexeme[0] == 'w'&& lexeme[1] == 'h'&& lexeme[2] == 'i' && lexeme[3] == 'l'&& lexeme[4] == 'e'){
           nextToken = WHILE_CODE;
			 break;
         }else if(lexeme[0] == 'd'&& lexeme[1] == 'o'){
           nextToken = DO_CODE;
			 break;
         }else if(lexeme[0] == 's'&& lexeme[1] == 'w'&& lexeme[2] == 'i' && lexeme[3] == 't'&& lexeme[4] == 'c' && lexeme[5] == 'h'){
           nextToken = SWITCH_CODE;
			 break;
         }else if(lexeme[0] == 'f'&& lexeme[1] == 'o'&& lexeme[2] == 'r' && lexeme[3] == 'e'&& lexeme[4] == 'a' && lexeme[5] == 'c' && lexeme[6]=='h'){
           nextToken = FOREACH_CODE;
			 break;
         }else if(lexeme[0] == 'r'&& lexeme[1] == 'e'&& lexeme[2] == 't' && lexeme[3] == 'u'&& lexeme[4] == 'r' && lexeme[5] == 'n'){
           nextToken = RETURN_CODE;
			 break;
         }else if(lexeme[0] == 'f'&& lexeme[1] == 'l'&& lexeme[2] == 'o' && lexeme[3] == 'a'&& lexeme[4] == 't'){
           nextToken = FLOAT_CODE;
			 break;
         }else if(lexeme[0] == 'e'&& lexeme[1] == 'l'&& lexeme[2] == 's' && lexeme[3] == 'e'){
           nextToken = ELSE_CODE;
			 break;
         }else if(lexeme[0] == 'i'&& lexeme[1] == 'n' && lexeme[2] == 't'){
           nextToken = INT_CODE;

			 break;
         }
         else{
			 nextToken = IDENT;
			 break;}

		//int
		 case DIGIT:
			 addChar();
			 getChar();
      
       while (charClass == DIGIT||nextChar =='.'||nextChar =='e'||nextChar =='E') {
         if(nextChar =='.'||nextChar == 'e' || nextChar =='E' ){
           if(_float!=1){
             _float=1;
           }else{
             
           }
           
         }
         
				 addChar();
				 getChar();
			 }
       if(_float!=1){
        nextToken = INT_LIT;
        
        }
        else{
       nextToken = FLOAT;}
		 	break;

       //floating points
       case FLOAT:
			 addChar();
			 getChar();
			 
       while (charClass == DIGIT) {
				 addChar();
				 getChar();
			 }

			 nextToken = FLOAT;
       
		 	break;
       //FOR
       case FOR:
			 addChar();
			 getChar();
			 
       while (charClass == FOR) {
				 addChar();
				 getChar();
			 }

			 nextToken = FOR;
       
		 	break;

		//PARANTHESES AND OPS
		 case UNKNOWN:
			 lookup(nextChar);
			 getChar();
			 break;

			//LEX
		case EOF:
			 nextToken = EOF;
			 lexeme[0] = 'E';
			 lexeme[1] = 'O';
			 lexeme[2] = 'F';
			 lexeme[3] = '\0';
		 	break;
	 } //end of SWITCH
   printf("\n");
	 printf("Next token is: %d, Next lexeme is %s\n",
	 nextToken, lexeme);
	 return nextToken;
} 
void void_check(void) {
	 
	//determien RHS
	 if (nextToken == IDENT && lexeme[0] == 'v'&& lexeme[1] == 'o'&& lexeme[2] == 'i'&& lexeme[3] == 'd'){
		
           printf("Enter <void>\n");
           lex();
           main_check();
		
	 }else{
     
      printf("Missing <void> ");
      error();
    
		
   }
	 printf("Exit <void>\n");
   
   error2();
}
void main_check(void) {
	 
	//determine RHS
	 if (nextToken == IDENT && lexeme[0] == 'm'&& lexeme[1] == 'a'&& lexeme[2] == 'i'&& lexeme[3] == 'n'){
		
           printf("Enter <main>\n");
           lex();
           if (nextToken == LEFT_PAREN) {
		       lex();
		 if (nextToken == RIGHT_PAREN){
		 	lex();
       block_check();
     }else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }else{
       printf("Missing <Left Parenthesis> ");
		 	error();
     }
		
	 }else{
     
      printf("Missing <main> ");
      error();
    
		
   }
	 printf("Exit <main>\n");
}
void block_check(void) {
	 
	
    if (nextToken == LEFT_BLOCK) {
      printf("Enter <BlOCK>\n");
		  lex();
      
      while(nextToken != RIGHT_BLOCK){
        lex();
        statement();
      
      }
      
		if (nextToken == RIGHT_BLOCK){
      lex();
      
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
	     printf("Exit <BlOCK>\n");
       
     }

void expr(void) {
	 printf("Enter <expr>\n");
	//parsing
	 term();
	//prase if + or -
	 while (nextToken == ADD_OP || nextToken == SUB_OP ||nextToken==SEMICOLON_CODE ) {
		 lex();
		 term();
	 }
	 printf("Exit <expr>\n");
}


void statement(){
switch(nextToken) {

   case FOR_CODE  :
   printf("Enter <For>\n");
   lex();

     if (nextToken == LEFT_PAREN) {
       lex();
       printf("%d <For>\n",nextToken);
       while(nextToken != COLON_CODE){
         expr();
      }
       
       lex();
       while(nextToken != COLON_CODE){
         expr();
      }
      lex();
      while(nextToken != RIGHT_PAREN){
         expr();
      }
     // lex();
		 if (nextToken == RIGHT_PAREN){
		 	lex();
       
     }else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }else{
       printf("Missing <Left Parenthesis> ");
		 	error();
     }
     
if (nextToken == LEFT_BLOCK) {
      
		  lex();
      statement();
      
		if (nextToken == RIGHT_BLOCK){
    lex();
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
	     printf("Exit <For>\n");
       lex();
     
     
      
       
      break; 
	
   case LEFT_BLOCK  :
     
       block_check();
      break; 

      case RIGHT_BLOCK  :
     
       
      break; 
  
  case IF_CODE  :
  printf("Enter <IF>\n");
     lex();
     if (nextToken == LEFT_PAREN) {
       lex();
       expr();
      
       
       
		 if (nextToken == RIGHT_PAREN){
		 	lex();
       
     }else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }else{
       printf("Missing <Left Parenthesis> ");
		 	error();
     }
     if (nextToken == LEFT_BLOCK) {
      
		  lex();
      statement();
      
		if (nextToken == RIGHT_BLOCK){
		 	lex();
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
     
	     printf("Exit <IF>\n");
       lex();
       


       if(nextToken==ELSE_CODE){
         
         lex();
         if (nextToken == LEFT_BLOCK) {
      
		  lex();
      statement();
      
		  if (nextToken == RIGHT_BLOCK){
        printf("Exit <else>\n");
		 	 lex();
         
      }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		  }else{
      printf("Missing <Left BLOCK> ");
		 	error();
      }
      
       }
             break; 

  case DO_CODE  :
  printf("Enter <DO-While>\n");
     lex();
       if (nextToken == LEFT_BLOCK) {
      
		  lex();
      statement();
      
		 if (nextToken == RIGHT_BLOCK){
       lex();
		 	 if(nextToken == WHILE_CODE){
       printf("Enter <while>\n");
       lex();
     if (nextToken == LEFT_PAREN) {
       lex();
       expr();
     if (nextToken == RIGHT_PAREN){
		 	
       
     }else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }else{
       printf("Missing <Left Parenthesis> ");
		 	error();
     }
        }else{
           printf("Missing <while>\n ");
        }
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
     
     
	     printf("Exit <do-while>\n");
       lex();
      break;

  case WHILE_CODE  :
      printf("Enter <while>\n");
     lex();
     if (nextToken == LEFT_PAREN) {
       lex();
       expr();
      if (nextToken == RIGHT_PAREN){
		 	lex();
       
     }else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }else{
       printf("Missing <Left Parenthesis> ");
		 	error();
     }
     if (nextToken == LEFT_BLOCK) {
      
		  lex();
      statement();
      
		if (nextToken == RIGHT_BLOCK){
		 	 
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
	     printf("Exit <while>\n");
       lex();
      break; 
  case RETURN_CODE  :
  printf("Enter <return>\n");
     lex();
     expr();
     printf("Exit <return>\n");
       
      break; 

  case SWITCH_CODE  :
     
        printf("Enter <switch>\n");
   lex();

     if (nextToken == LEFT_PAREN) {
       lex();
       expr();
       
		 if (nextToken == RIGHT_PAREN){
		 	lex();
       
     }else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }else{
       printf("Missing <Left Parenthesis> ");
		 	error();
     }

     if (nextToken == LEFT_BLOCK) {
      
		  lex();
      statement();
      
		if (nextToken == RIGHT_BLOCK){
		 	 
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
	     printf("Exit <switch>\n");
       lex();
     
      break; 

  case ASSIGN_OP  :
  printf("Enter <Assign>\n");
     lex();
     expr();
     
     
       printf("Exit <Assign>\n");
      break; 
      
      case FOREACH_CODE  :
      printf("Enter <foreach>\n");
     
     lex();
     if (nextToken == LEFT_PAREN) {
       lex();
       expr();
      
       
       
		 if (nextToken == RIGHT_PAREN){
		 	lex();
       
     }else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }else{
       printf("Missing <Left Parenthesis> ");
		 	error();
     }
     if (nextToken == LEFT_BLOCK) {
      
		  lex();
      statement();
      
		if (nextToken == RIGHT_BLOCK){
		 	 
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
	     printf("Exit <foreach>\n");
       lex();
      break; 
      
      default: 
      lex();
      statement();
      break;

}
 
}


void factor(void) {
	 printf("Enter <factor>\n");
	
	 if (nextToken == IDENT || nextToken == INT_LIT){
		
		 lex();
	// if RHS is <expr> then call lex, pass L parantheses, call expr, and check R parantheses
	 }else { 
     if (nextToken == LEFT_PAREN) {
		 lex();
		 expr();
		 if (nextToken == RIGHT_PAREN){
		 	lex();
     }else{
		 	error();
       }
		 }
		 else{
		  
	 }
	 printf("Exit <factor>\n");
}}