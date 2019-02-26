/* CS261- Assignment 1 - Q.3*/
/* Name: Jonathan Jazdzewski
 * Date: 10/8/18
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>



char toUpperCase(char ch){
    ch = ch - 32;
    return ch;
}

char toLowerCase(char ch){
      ch = ch + 32;
      return ch;
}

int stringLength(char s[]) {
   int i = 0;
   while (s[i]!='\0'){
       i++;
   }
   return i;
}


void camelCase(char* word){
	int leng = stringLength(word);
    for (int a=0; a<leng;a++){
        if (word[a]==95){
            word[a+1] = toUpperCase(word[a+1]);
            leng = leng-1;
            for (int b=a;b<leng+1;b++){
                word[b] = word[b+1];
            }
        }
    }
}

int main(){

	char s[20];
    gets(s);
    int length = stringLength(s);
    int count = 0;
    int chara = 0;
    for (int z=0; z<length;z++){
        if (s[z]>64 && s[z]<91){
            chara = 1;
            break;
        } else if (s[z]>96 && s[z]<123){
            chara = 1;
            break;
        }
    }
    if (chara==0){
        printf("Invalid input string.");
    }
    while (1==1){
        if (s[count]=='\0'){
            break;
        } else if (s[count]==95 && count<1){
            for (int d=count;d<length;d++){
                s[d] = s[d+1];
            }
            length = length -1;
        } else if (s[count]>96 && s[count] < 123){
            count++;
        } else if ((s[count-1]>96 && s[count-1] < 123) && s[count] == 95 ){
            count++;
        } else if (s[count]>64 && s[count] < 91){
            s[count] = toLowerCase(s[count]);
        } else if (( s[count]<65 || (s[count]<97 && s[count]>90) || s[count]>122) && (s[count-1] > 96 && s[count-1] < 123 ) ){
            s[count] = 95;
            count++;
        } else if (s[count]<65 || (s[count]<97 && s[count]>90) || s[count]>122){
            for (int c=count;c<length;c++){
                s[c] = s[c+1];
            }
            length = length -1;
        }
    }
    if (chara==1){
	    camelCase(s);
	    printf("%s",s);
    }
	/*Call camelCase*/


	/*Print the new string*/


	return 0;
}

