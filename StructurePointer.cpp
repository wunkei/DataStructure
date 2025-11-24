#include <iostream>
using namespace std;

typedef struct{
    int x;
    int y;
}po;
int main(){
    po* test=(po*)malloc(sizeof(po));
    test->x=5;
    test->y=10;
    printf("%d\n",test->x);
    printf("%d\n",test->y);
    return 0;
}