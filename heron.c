#include<stdio.h>
#include <math.h>

double a = 5;
double b = 6;
double c = 8;
double area;
char output[] = "The area of the triangle is: ";

int main(){
    double abc = a+b+c;
    double mabc = b+c-a;
    double ambc = a+c-b;
    double abmc = a+b-c;
    double rooted = abc*mabc*ambc*abmc;
    double root = sqrt(rooted);
    double ans = root/4;
    printf("%s",output);
    printf("%f",ans);
    printf("%s",".");
    return 0;
}
