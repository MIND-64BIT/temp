
#include<stdio.h>
#include<string.h>

int maxsize = 3;
int size = 0, arr[3] = {};


int push(int val){

    if(size == maxsize){
        printf("IndexError: stack is full\n");
        return 1;
    }

    arr[size] = val;
    size += 1;

    return 0;
}

int pop(){

    int lastElement = arr[size-1];

    if(size == 0){
        printf("\nIndexError: stack is empty\n");
        return -1;
    }

    size -= 1;

    return lastElement;
}

void display(){

    if(size == 0){
        printf("\nstack is empty\n");
        return;
    }

    printf("\nSTACK: \n");

    for(int i=0; i != size; i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
    return;
}

int main(){

    int choice;
    int val;
    int popedElement;

    while(1){

        printf("\n1. Push\n2. Pop\n3. Display\nEnter a Choice: ");
        scanf("%d", &choice);

        switch( choice ){

        case 1:

            printf("\nEnter value: ");
            scanf("%d",&val);

            int isFull = push(val);
            char bool1[7];

            if(isFull == 0){
                printf("%d is pushed in the STACK\n",val);
            }
            else{
                printf("\nDo you want to increase the size of stack\n");
                printf("\(yes/no\) ");
                scanf("%s",bool1);

                if(strcmp(bool1,"yes") == 0){
                    printf("increase");
                }
                else{
                    printf("no increase");
                }
           }

            break;

        case 2:

            popedElement = pop();
            if(popedElement != -1){
                printf("%d is removed from the STACK\n",popedElement);
            }
            break;

        case 3:

            display();
            break;

        default:

            printf("InputError: invalid input\n");
            break;
        }


    }
return 0;

}
