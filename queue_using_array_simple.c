
#include<stdio.h>
#define size 50


int arr[size],front = -1, rear = -1;


void enqueue(val){

    if(rear >= size){
        printf("\nIndexError: queue is full");
        return;
    }
    else if(front > -1 && front >= rear){
        printf("\nIndexError: queue is full");
        return;
    }
    if(rear == -1 && front == -1){
        front += 1;
    }
    rear += 1;
    arr[rear] = val;

    return;
}

int dequeue(){
    int first_ele;

    if(front == -1){
        printf("\nIndexError: queue is empty");
        return -1;
    }

    first_ele = arr[front];
    front += 1;

    return first_ele;
}


void display(){

    for(int i = front; i <= rear; i++){
        printf("%d\t",arr[i]);
    }


    return;
}


int main(){

    int option, value, dequeue_val;

    while(1){

        printf("\n1.Enqueue\n2.Dequeue\n3.Display\n4.Exit\nChoice: ");
        scanf(" %d",&option);

        switch(option){

            case 1:
                printf("\nEnter value to enqueue: ");
                scanf(" %d",&value);

                enqueue(value);
                break;

            case 2:

                dequeue_val = dequeue();
                printf("\n%d is removed", dequeue_val);

            case 3:
                display();
                printf("%d %d %d",front,rear,size);
                break;

            case 4:
                return 0;

            default:
                printf("\nEnter a valid option");



        }
    }

    return 0;

}
