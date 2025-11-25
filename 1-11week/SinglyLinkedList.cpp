#include <iostream>
#include <cstdlib>
using namespace std;

typedef int ElemType;

typedef struct Sld{
    ElemType data;
    struct Sld* Nextpointer;
}Sld;

Sld* initSld(){
    Sld* demo = (Sld*)malloc(sizeof(Sld));
    demo->data=0;
    demo->Nextpointer=NULL;
    return demo;
}

void setSldInHead(Sld* sld,ElemType DATA){
    Sld* demo = (Sld*)malloc(sizeof(Sld));
    demo->data = DATA;
    demo->Nextpointer = sld->Nextpointer;
    sld->Nextpointer = demo;
}

void setSldInTail(Sld* sld,ElemType DATA){
    Sld* demo = (Sld*)malloc(sizeof(Sld));
    demo->data = DATA;
    demo->Nextpointer = NULL;
    while(sld->Nextpointer != NULL)
    sld = sld->Nextpointer;
    sld->Nextpointer = demo;
}

void delSld(Sld* sld,int num){
    
    for(int i = 1;i < num;++i){
        if(sld->Nextpointer==NULL){
            cout<<"大于范围"<<endl;
            return;}
        sld=sld->Nextpointer;
    }
    if(num<=0){
        cout<<"小于范围"<<endl;
        return;}
    sld->Nextpointer = sld->Nextpointer->Nextpointer;
}

void displaySld(Sld* sld){
    sld = sld->Nextpointer;
    while(sld!=NULL){
        printf("%d\n",sld->data);
        sld = sld->Nextpointer;
    }
}

int main(){
    Sld* p = initSld();
    setSldInTail(p,5);
    setSldInTail(p,10);
    setSldInTail(p,15);
    delSld(p,0);
    displaySld(p);
}