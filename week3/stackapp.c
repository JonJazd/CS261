/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */
char stack[40];
int topSpot = -1;
void push(char c){
	topSpot++;
	stack[topSpot] = c;
}
void pop(){
	topSpot--;
}
char top(){
	return stack[topSpot];
}
int isEmpty(){
	if (topSpot==-1){
		return 1;
	} else {
		return 0;
	}
}
/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
int i = -1;
char nextChar(char* s)
{
	char c;
	i++;	
	c = *(s+i);
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	if (s!=NULL){
        char a = nextChar(s);
		char openParen = '(';
		char openBrack = '[';
		char openCurl = '{';
		char closeParen = ')';
		char closeBrack = ']';
		char closeCurl = '}';
        while (a!='\0'){
            if (a!=openParen && a!=openCurl && a!=openBrack && a!=closeCurl && a!=closeBrack && a!=closeParen){
				
                a = nextChar(s);
            } else if (a==openParen || a==openCurl || a==openBrack){
				//printf("pushing: %d\n",a);
                push(a);
				a = nextChar(s);
            } else if (a==closeCurl && top()!=openCurl){
				//printf("No closed curl\n");
                return 0;
            } else if (a==closeParen && top()!=openParen){
				//printf("No close paren\n");
                return 0;
            } else if (a==closeBrack && top()!=openBrack){
				//printf("No closed brack\n");
                return 0;
            } else if (a==closeCurl || a==closeBrack || a==closeParen){
				//printf("Popping\n");
                pop();
				a = nextChar(s);
            }
        }
        if (!isEmpty()){
			//printf("isn't empty\n");
            return 0;
        }
    } else {
        return 0;
    }
	return 1;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

