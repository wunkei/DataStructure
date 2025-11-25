#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

int main(){
    char* a;
    a = (char*)malloc(10);
    strcpy(a,"HelloWorld");
    printf("%s",a);

}