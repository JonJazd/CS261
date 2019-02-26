/* CS261- Assignment 1 - Q. 0*/
/* Name: Jonathan Jazdzewski
 * Date: 10/8/18
 * Solution description:
 */
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
void fooA(int* iptr){
    char value[] = "Value: ";
    char address[] = "Address: ";
    printf("%s",value);
    printf("%d\n",*iptr);
    printf("%s",address);
    printf("%x\n",iptr);
}
void fooB(int* jptr){
    char value[] = "Value: ";
    char address[] = "Address: ";
    printf("%s",value);
    printf("%d\n",*jptr);
    printf("%s",address);
    printf("%x\n",jptr);
    jptr = jptr - 1;
    printf("%s",address);
    printf("%x\n",jptr);
}
int main(){
    int x;
    char value[] = "Value: ";
    char address[] = "Address: ";
    x = rand() % 11;
    printf("%s", value);
    printf("%d\n",x);
    printf("%s",address);
    printf("%x\n",&x);
    fooA(&x);
    printf("%s", value);
    printf("%d\n",x);
    //fooA and main should print the same values
    fooB(&x);
    printf("%s", value);
    printf("%d\n",x);
    printf("%s",address);
    printf("%x\n",&x);
    //fooB and main will print different values
    return 0;
}



