
#include<stdio.h>
int size=3, arr[100]={1,2,3};


void insert(int idx, int val){

    if(idx > size || idx < 0){
        printf("IndexError: index out of range");
        return;
    }

    int i = size;
    for(i; i != idx; i--){
        arr[i] = arr[i-1];
    }

    arr[i] = val;
    size += 1;

    return;
}

void delete(int idx){

    if(idx > size-1 || idx < 0){
        printf("IndexError: index out of range");
        return;
    }
    else if(size == 0){
        printf("IndexError: deleting from empty array");
        return;
    }

    for(idx; idx != size; idx++){
        arr[idx] = arr[idx + 1];
    }

    size -= 1;

    return;
}


void update(int idx, int newVal){

    if(idx > size-1 || idx < 0){
        printf("IndexError: index out of range");
        return;
    }
    else if(size == 0){
        printf("IndexError: updating in empty array");
        return;
    }

    arr[idx] = newVal;

    return;
}


int main(){


    update(3,7);

    for(int j = 0; j != size; j++){
        printf("%d ", arr[j]);
    }

    printf("\n%d",size);




return 0;
}
