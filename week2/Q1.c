/* CS261- Assignment 1 - Q.1*/
/* Name: Jonathan Jazdzewski
 * Date:10/8/18
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef struct student student;
struct student{
	int id;
	int score;
};

struct student* allocate(){
    struct student stu;
    struct student * array;
    array = (struct student*) malloc(10*sizeof(stu));

    return array;
}

void generate(struct student* students){
    for (int i=0;i<10;i++){
        int boo = 1;
        int same = 0;
        int ID;
        while (boo == 1){
            ID = (rand() % 10) + 1;

            for (int k = 0; k<i;k++){
                if (students[k].id==ID){
                    same = 1;
                }
            }
            if (same==0){
                boo = 0;
            }
            same = 0;
        }

        if (same==0){
            students[i].id = ID;
        }
        same = 0;
        int score = rand() % 101;
        students[i].score = score;
    }
     /*Generate random and unique IDs and random scores for ten students,
IDs being between 1 and 10, scores between 0 and 100*/

}

void output(struct student* students){
    for (int a = 0; a<10; a++){
        printf("%d",students[a].id);
        printf(" ");
        printf("%d",students[a].score);
        printf("\n");
    }
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
}

void summary(struct student* students){
    int max = 0;
    int min = 100;
    int avg = 0;
    for (int b= 0; b<10; b++){
        if (students[b].score>max){
            max = students[b].score;
        }
        if (students[b].score<min){
            min = students[b].score;
        }
        avg += students[b].score;
    }
    avg = avg/10;
    printf("Max: ");
    printf("%d\n",max);
    printf("Min: ");
    printf("%d\n",min);
    printf("Average: ");
    printf("%d\n",avg);
     /*Compute and print the minimum, maximum and average scores of the
ten students*/

}

void deallocate(struct student* stud){
    free(stud);
     /*Deallocate memory from stud*/
}

int main(){
    struct student* stud = NULL;
    stud = allocate();

    /*Call allocate*/
    generate(stud);

    /*Call generate*/
    output(stud);

    /*Call output*/
    summary(stud);

    /*Call summary*/
    deallocate(stud);
    /*Call deallocate*/

    return 0;
}

