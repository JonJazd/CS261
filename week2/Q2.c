/* CS261- Assignment 1 - Q.2*/
/* Name:Jonathan Jazdzewski
 * Date:10/8/18
 * Solution description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    int* d = a;
    a = b;
    b = d;
    c = c-1;
    return c;

    /*Decrement the value of integer variable c*/

    /*Return c*/
}

int main(){
    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x = rand() % 11;
    int y = rand() % 11;
    int z = rand() % 11;
    /*Print the values of x, y and z*/
    printf("%d\n",x);
    printf("%d\n",y);
    printf("%d\n",z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    int w = foo(&x,&y,z);
    /*Print the values of x, y and z*/
    printf("%d\n",x);
    printf("%d\n",y);
    printf("%d\n",z);
    /*Print the value returned by foo*/
    printf("%d\n",w);

    return 0;
}




